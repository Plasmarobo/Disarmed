
#include <Wire.h>

#define I2C_TIMEOUT_MS 2000

#define I2C_SUCCESS 0
#define I2C_BUFFER_OVERRUN 1
#define I2C_NACK_ADDR 2
#define I2C_NACK_DATA 3
#define I2C_OTHER_ERR 4

#define READ_TIMEOUT 0x89
#define VERIFY_FAILURE 0x88

enum ControlMode : uint8_t
{
  Demo = 0,
  Slave = 1
};

// Message format: Reg, Len, Data
enum Commands : uint8_t 
{
  Noop = 0,
  SetRegister = 1,
  GetRegister = 2,
  SetOutput = 3,
  GetOutput = 4,
  GetVersion = 5,
  SetOutputIndex = 6
};

enum CommunicationState: uint8_t
{
  Idle = 0,
  Confirm = 1,
  Data = 2
};

#define ERROR_FLAG 0x80

enum ErrorCode : uint8_t
{
  UnknownOperation = 0,
  InvalidIndex = 1,
  InvalidDataSize = 2
};

class LedBoardDriver
{
  private:
    uint8_t i2c_addr;
    uint8_t buffer_length;
    uint8_t *led_buffer;

    uint8_t VerifyReply(uint8_t value)
    {
      uint8_t reply = 0;
      uint8_t status = Read(&reply, 1);
      if (status != I2C_SUCCESS)
      {
        return status;
      }
      if (reply == value)
      {
        return I2C_SUCCESS;
      }
      return VERIFY_FAILURE;
    };

    uint8_t SetRegister(uint8_t reg, uint8_t &value)
    {
      // Set Register writes 2 bytes:
      // Register Index
      // Value to set
      uint8_t buffer[3] = { Commands::SetRegister, reg, value };
      uint8_t status = Write(buffer, 3);
      if (status != I2C_SUCCESS)
      {
        return status;
      }
      return VerifyReply(value);
    };
    
    uint8_t GetRegister(uint8_t reg, uint8_t &value)
    {
      // Get Register writes 1 byte:
      // Register to query
      uint8_t buffer[2] = { Commands::GetRegister, reg };
      uint8_t status = Write(buffer, 2);
      if (status != I2C_SUCCESS)
      {
        return status;
      }
      status = VerifyReply(reg);
      if (status != I2C_SUCCESS)
      {
        return status;
      }
      return Read(&value, 1);
    };
    
    uint8_t SetOutput(uint8_t *value)
    {
      // Set output sends a whole or partial buffer
      // Here we only send a whole buffer
      uint8_t* buffer = new uint8_t[1 + buffer_length];
      buffer[0] = Commands::SetOutput;
      for(uint8_t i = 0; i < buffer_length; ++i)
      {
        buffer[i+1] = value[i];
      }
      uint8_t status = Write(buffer, 1+buffer_length);
      if (status != I2C_SUCCESS)
      {
        return status;
      }
      return VerifyReply(0);
    };
    
    uint8_t GetOutput(uint8_t *value)
    {
      uint8_t cmd = Commands::GetOutput;
      uint8_t status = Write(&cmd, 1);
      if (status != I2C_SUCCESS)
      {
        return status;
      }
      uint8_t response = 0;
      status = Read(&response, 1);
      if (status != I2C_SUCCESS)
      {
        return status;
      }
      return Read(value, buffer_length);
    };
    
    uint8_t GetVersion(uint8_t &value)
    {
      uint8_t cmd = Commands::GetVersion;
      uint8_t status = Write(&cmd, 1);
      if (status != I2C_SUCCESS)
      {
        return status;
      }
      return Read(&value, 1);
    };
    
    uint8_t SetOutputIndex(uint8_t &value)
    {
      uint8_t buffer[2] = { Commands::SetOutputIndex, value };
      uint8_t status = Write(buffer, 2);
      if (status != I2C_SUCCESS)
      {
        return status;
      }
      return VerifyReply(value);
    };

    uint8_t Write(uint8_t* buffer, uint8_t length)
    {
      Wire.beginTransmission(i2c_addr >> 1);
      Wire.write(buffer, length);
      return Wire.endTransmission();
    };
    
    uint8_t Read(uint8_t* buffer, uint8_t length)
    {
      uint8_t status = READ_TIMEOUT;
      uint32_t timeout = millis() + I2C_TIMEOUT_MS;
      Wire.requestFrom(i2c_addr, length);
      delay(5); // Let the slave respond
      uint8_t index = 0;
      while ((Wire.available() > 0)
             && (millis() < timeout)
             && (index < length))
      {
        buffer[index] = Wire.read();
        ++index;
      }
      if (index == length)
      {
        return I2C_SUCCESS;
      }
      return status;
    };

    void ResetOutputIndex()
    {
      uint8_t index = 0;
      Serial.printf("SetOutputIndex: %d", SetOutputIndex(index));
      Serial.println();
    };

  public:
    LedBoardDriver(uint8_t buffer_len, uint8_t addr)
    {
      Wire.begin();
      buffer_length = buffer_len;
      i2c_addr = addr;
      led_buffer = new uint8_t[buffer_length];
    };

    ~LedBoardDriver()
    {
      delete [] led_buffer;
    };

    void SetSlaveMode()
    {
      uint8_t mode = ControlMode::Slave;
      Serial.printf("Set register: %d", SetRegister(Commands::SetRegister, mode));
      Serial.println();
    };

    void WriteBuffer()
    {
      ResetOutputIndex();
      Serial.printf("SetOutput: %d", SetOutput(led_buffer));
      Serial.println();
    };

    void SetLed(uint8_t index, uint8_t digit, uint8_t state)
    {
      if (index < buffer_length)
      {
        if (digit < 8)
        {
          if (state)
          {
            led_buffer[index] |= 0x01 << digit;
          } else {
            led_buffer[index] &= ~(0x01 << digit);
          }
        }
      }
    };

    void SetChunk(uint8_t index, uint8_t chunk)
    {
      if (index < buffer_length)
      {
        led_buffer[index] = chunk;
      }
    };

    void SetBuffer(uint8_t* data)
    {
      memcpy(led_buffer, data, buffer_length);
    };

    uint8_t GetVersion()
    {
      uint8_t version = 0;
      Serial.printf("GetVersion: %d", GetVersion(version));
      Serial.println();
      return version;
      
    }
};

#define LED_ADDR 0xE4
#define N_LED_BYTES 11

LedBoardDriver slave(N_LED_BYTES, LED_ADDR);
uint8_t energized_byte = 0;
uint32_t timer = 0;

void setup() {
  Serial.begin(115200);
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);
  delay(50);
  digitalWrite(12, HIGH);
  delay(500);
  slave.SetSlaveMode();
}

void loop()
{
  if (millis() > timer)
  {
    timer = millis() + 1000;
    slave.SetChunk(energized_byte, 0xFF);
    slave.WriteBuffer();
    delay(500);
    slave.SetChunk(energized_byte, 0x00);
    slave.WriteBuffer();
    delay(500);
    ++energized_byte;
    if (energized_byte > N_LED_BYTES)
    {
      energized_byte = 0;
    }
  }
    
}
