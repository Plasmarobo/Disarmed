#include <SPI.h>
#include <stdlib.h>
#include <time.h>

void wait(uint32_t ms)
{
  while(ms > 0)
  {
    uint32_t window = ms > 100 ? 100 : ms;
    ms -= window;
    delay(ms);
    yield();
    ESP.wdtFeed();
  }
}

const uint8_t POT_SEL_PIN = 0;
const uint8_t SSD_LOAD_PIN = 15;
const uint8_t SPI_DATA_PIN = 13;
const uint8_t SPI_CLK_PIN = 12;

const uint8_t MCP41XXX_COMMAND_NOOP = 0x00;
const uint8_t MCP41XXX_COMMAND_WRITE = 0x10;
const uint8_t MCP41XXX_COMMAND_SHUTDOWN = 0x20;

const uint8_t MCP41XXX_POT_0 = 0x01;
const uint8_t MCP41XXX_POT_1 = 0x02;
// MCP41XXX control
// Function also wakes device after shutdown
void SetupMCP41XXX()
{
  pinMode(POT_SEL_PIN, OUTPUT);
  digitalWrite(POT_SEL_PIN, HIGH);
}

void WriteMCP41XXX(uint8_t command, uint8_t data)
{
  digitalWrite(POT_SEL_PIN, LOW);
  SPI.transfer(command);
  SPI.transfer(data);
  digitalWrite(POT_SEL_PIN, HIGH);
}

void SetMCP41XXX(uint8_t value)
{
  WriteMCP41XXX(MCP41XXX_COMMAND_WRITE | MCP41XXX_POT_0, value);
}

void SleepMCP41XXX()
{
  WriteMCP41XXX(MCP41XXX_COMMAND_SHUTDOWN | MCP41XXX_POT_0 | MCP41XXX_POT_1, 0);
}

const uint8_t MAX72XX_DEVICE_COUNT = 4;
const uint8_t MAX72XX_SCAN_LIMIT = 0x07;
const uint8_t MAX72XX_INTENSITY = 0;
static_assert(MAX72XX_INTENSITY < 16, "Intensity Maximum is 15");
static_assert(MAX72XX_INTENSITY >= 0, "Intensity Minimum is 0");

// Special encoding to locate hex values at native positions
const uint8_t charTable[] = {
    B01111110,B00110000,B01101101,B01111001,B00110011,B01011011,B01011111,B01110000,
    B01111111,B01111011,B01110111,B00011111,B00001101,B00111101,B01001111,B01000111,
    B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
    B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
    B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
    B00000000,B00000000,B00000000,B00000000,B10000000,B00000001,B10000000,B00000000,
    B01111110,B00110000,B01101101,B01111001,B00110011,B01011011,B01011111,B01110000,
    B01111111,B01111011,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
    B00000000,B01110111,B00011111,B00001101,B00111101,B01001111,B01000111,B00000000,
    B00110111,B00000000,B00000000,B00000000,B00001110,B00000000,B00000000,B00000000,
    B01100111,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
    B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00001000,
    B00000000,B01110111,B00011111,B00001101,B00111101,B01001111,B01000111,B00000000,
    B00110111,B00000000,B00000000,B00000000,B00001110,B00000000,B00010101,B00011101,
    B01100111,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
    B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000
};

const uint8_t INTENSITY_MAP[MAX72XX_DEVICE_COUNT] = {
  1,
  3,
  7,
  1
};

enum MAX72XXAddress : uint8_t
{
  NOOP =    0x00,
  DIGIT0 =  0x01,
  DIGIT1 =  0x02,
  DIGIT2 =  0x03,
  DIGIT3 =  0x04,
  DIGIT4 =  0x05,
  DIGIT5 =  0x06,
  DIGIT6 =  0x07,
  DIGIT7 =  0x08,
  DECODEMODE = 0x09,
  INTENSITY = 0x0A,
  SCANLIMIT = 0x0B,
  SHUTDOWN = 0x0C,
  DISPLAYTEST = 0x0F
};

struct MAX72XXMessage
{
  uint8_t address;
  uint8_t data;
};

MAX72XXMessage message_buffer[MAX72XX_DEVICE_COUNT];

void ClearMAX72XXBuffer()
{
  memset(message_buffer, 0, sizeof(message_buffer));
}

void CommitMAX72XXBuffer()
{
  // This may need to be reversed
  digitalWrite(SSD_LOAD_PIN, LOW);
  SPI.transfer(reinterpret_cast<uint8_t*>(message_buffer), sizeof(message_buffer));
  digitalWrite(SSD_LOAD_PIN, HIGH);
  yield();
  ClearMAX72XXBuffer();
}

void WakeUpMAX72XX(uint32_t device)
{
  message_buffer[device].address = MAX72XXAddress::SHUTDOWN;
  message_buffer[device].data = 1;
}

void ShutdownMAX72XX(uint32_t device, bool shutdown)
{
  message_buffer[device].address = MAX72XXAddress::SHUTDOWN;
  message_buffer[device].data = shutdown ? 0 : 1;
}

void IntensityMAX72XX(uint32_t device, uint8_t value)
{
  if (value > 15)
  {
    Serial.printf("Invalid Intensity Value: %d", value);
    Serial.println();
    value = 15;
  }
  message_buffer[device].address = MAX72XXAddress::INTENSITY;
  message_buffer[device].data = value;
}

void ScanLimitMAX72XX(uint32_t device, uint8_t limit)
{
  if (limit != 7)
  {
    Serial.println("This library only supports a scan limit of 8 to protect the MAX72XX");
    limit = 0x07;
  }
  message_buffer[device].address = MAX72XXAddress::SCANLIMIT;
  message_buffer[device].data = limit;
}

void DecodeModeMAX72XX(uint32_t device, uint8_t value)
{
  message_buffer[device].address = MAX72XXAddress::DECODEMODE;
  message_buffer[device].data = value;
}

void DisplayTestMAX72XX(uint32_t device, bool enable)
{
  message_buffer[device].address = MAX72XXAddress::DISPLAYTEST;
  message_buffer[device].data = enable ? 1 : 0;
}

void DigitMAX72XX(uint32_t device, uint8_t digit, uint8_t value, bool dp)
{
  message_buffer[device].address = MAX72XXAddress::DIGIT0 + digit;
  message_buffer[device].data = value | (dp ? 0x80 : 0x00);
}

void SetCharMAX72XX(uint32_t device, uint8_t digit, char value, bool dp) {
    
    if (value < 0 || value > 127)
    {
      value = 32;
    }
    DigitMAX72XX(device, digit, value, dp);
}

void ClearDisplayMAX72XX()
{
  for(uint8_t digit = 0; digit < 8; ++digit)
  {
    for(uint32_t device = 0; device < MAX72XX_DEVICE_COUNT; ++device)
    {
      message_buffer[device].address = MAX72XXAddress::DIGIT0 + digit;
      message_buffer[device].data = 0;
    }
    CommitMAX72XXBuffer();
  }
}

void SetupMAX72XX()
{
  pinMode(SSD_LOAD_PIN, OUTPUT);
  digitalWrite(SSD_LOAD_PIN, HIGH);
  for(uint8_t i = 0; i < MAX72XX_DEVICE_COUNT; ++i)
  {
    ShutdownMAX72XX(i, false);
  }
  CommitMAX72XXBuffer();
  for(uint8_t i = 0; i < MAX72XX_DEVICE_COUNT; ++i)
  {
    ScanLimitMAX72XX(i, MAX72XX_SCAN_LIMIT);
  }
  CommitMAX72XXBuffer();
  for(uint8_t i = 0; i < MAX72XX_DEVICE_COUNT; ++i)
  {
    DecodeModeMAX72XX(i, 0);
  }
  CommitMAX72XXBuffer();
  for(uint8_t i = 0; i < MAX72XX_DEVICE_COUNT; ++i)
  {
    IntensityMAX72XX(i, INTENSITY_MAP[i]); 
  }
  CommitMAX72XXBuffer();
  for(uint8_t i = 0; i < MAX72XX_DEVICE_COUNT; ++i)
  {
    DisplayTestMAX72XX(i, true);
    CommitMAX72XXBuffer();
    wait(500);
    DisplayTestMAX72XX(i, false);
    CommitMAX72XXBuffer();
  }
  ClearDisplayMAX72XX();
}

// (Each device drives up to 8 digits)
const uint8_t DIGITS_PER_DEVICE = 8;
const uint32_t TOTAL_DIGITS = DIGITS_PER_DEVICE * MAX72XX_DEVICE_COUNT;

uint8_t digit_array[TOTAL_DIGITS];

// Writes a hex value into the digit array
void WriteHex(uint8_t device, uint32_t value)
{
  // Uses all 8 digits of a device to render a 4 byte value
  // First convert to characters
  for (int32_t digit = 0; digit < 8; ++digit)
  {
    uint8_t nybble = (value >> (4 * digit)) & 0x0F;
    // Char table is already formatted for us
    digit_array[(device * DIGITS_PER_DEVICE) + digit] = charTable[nybble];
  }
}

void UpdateDisplayHex()
{
  ClearDisplayMAX72XX();
  for (uint8_t digit = 0; digit < DIGITS_PER_DEVICE; ++digit)
  {
    for (uint32_t device = 0; device < MAX72XX_DEVICE_COUNT; ++device)
    {
      DigitMAX72XX(device, digit, digit_array[(device * DIGITS_PER_DEVICE) + digit], false);
    }
    CommitMAX72XXBuffer();
  }
}

/* we always wait a bit between updates of the display */
unsigned long delaytime=250;

void setup() {
  srand(time(NULL));
  Serial.begin(115200);
  SPI.begin();
  SetupMCP41XXX();
  SetMCP41XXX(255);
  SetupMAX72XX();
  Serial.println("Boot Complete");
}

uint32_t cycle = 0;

void loop() { 
    for(uint32_t device = 0; device < MAX72XX_DEVICE_COUNT; ++device)
    {
         WriteHex(device, rand());
    }
    UpdateDisplayHex();
    ++cycle;
    wait(delaytime);
}
