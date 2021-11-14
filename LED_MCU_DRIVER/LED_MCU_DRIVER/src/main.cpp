#include <Arduino.h>
#include <EEPROM.h>

// Firmware Version
#define FW_VERSION 0x03

// Shift Clock: Arduino Pin 3, PortB(3)
#define SHIFT_CLK_PIN 3

// Shift Latch: Arduino Pin 4, PortB(4)
#define SHIFT_LATCH_PIN 4

// Shift Data: Arduino Pin 1, PortB(1)
#define SHIFT_DATA_PIN 1

// I2C Slave pins
// I2C SDA, Arduino Pin 0, PortB(0)
#define I2C_SDA_PIN 0

// I2C SCL, Arduino Pin 2, PortB(2)
#define I2C_SCL_PIN 2

#define BYTE_TICK ((millis() << 10) % 255)

/**
 * Pin notes by Suovula, see also http://hlt.media.mit.edu/?p=1229
 *
 * DIP and SOIC have same pinout, however the SOIC chips are much cheaper, especially if you buy more than 5 at a time
 * For nice breakout boards see https://github.com/rambo/attiny_boards
 *
 * Basically the arduino pin numbers map directly to the PORTB bit numbers.
 *
// I2C
arduino pin 0 = not(OC1A) = PORTB <- _BV(0) = SOIC pin 5 (I2C SDA, PWM)
arduino pin 2 =           = PORTB <- _BV(2) = SOIC pin 7 (I2C SCL, Analog 1)
// Timer1 -> PWM
arduino pin 1 =     OC1A  = PORTB <- _BV(1) = SOIC pin 6 (PWM)
arduino pin 3 = not(OC1B) = PORTB <- _BV(3) = SOIC pin 2 (Analog 3)
arduino pin 4 =     OC1B  = PORTB <- _BV(4) = SOIC pin 3 (Analog 2)
 */
#define DEFAULT_I2C_SLAVE_ADDRESS 0x70 // the 7-bit address (remember to change this when adapting this example)
// Get this from https://github.com/rambo/TinyWire
#include <TinyWireS.h>
// The default buffer size, Can't recall the scope of defines right now
#ifndef TWI_RX_BUFFER_SIZE
#define TWI_RX_BUFFER_SIZE ( 35 )
#endif

#define EEPROM_I2C_ADDR 0

/*
 *  =============================
 *  Internal Register Definitions
 *  =============================
 */

#define REGISTER_COUNT 3
#define CONTROL_REGISTER_I2C_ADDR 0
#define CONTROL_REGISTER_BUFFERSTATE 1
#define CONTROL_REGISTER_MODE 2

#define BUFFERSTATE_CLEAN 0
#define BUFFERSTATE_DIRTY 1

#define OUTPUT_REGISTER_COUNT 11

enum ControlMode : uint8_t
{
  Demo = 0,
  Slave = 1
};

uint8_t registers[REGISTER_COUNT] = {
  DEFAULT_I2C_SLAVE_ADDRESS,
  BUFFERSTATE_CLEAN,
  ControlMode::Demo
};

// Number of 8 bit shift registers
uint8_t output_registers[OUTPUT_REGISTER_COUNT] = {
  0x55,
  0x55,
  0x55,
  0x55,
  0x55,
  0x55,
  0x55,
  0x55,
  0x55,
  0x55,
  0x55
};

// I2C Protocol: The master writes a command mode to the device
// The device updates it's internal state, then responds with
// A confirmation code, or the requested data
// In most cases, the confirmation code is set by the operation
// or is an echo of data sent to the device


uint8_t test_mode_clk = 0;

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

uint8_t current_op = Commands::Noop;

enum CommunicationState: uint8_t
{
  Idle = 0,
  Confirm = 1,
  Data = 2
};

uint8_t comm_state = CommunicationState::Idle;

uint8_t output_pointer;
uint8_t register_query;
uint8_t confirm_value;

#define ERROR_FLAG 0x80
#define SUCCESS_MASK 0xEF

enum ErrorCode : uint8_t
{
  UnknownOperation = 0,
  InvalidIndex = 1,
  InvalidDataSize = 2
};

uint8_t read_i2c_addr()
{
  return EEPROM.read(EEPROM_I2C_ADDR);
}

void write_i2c_addr(uint8_t addr)
{
  EEPROM.write(EEPROM_I2C_ADDR, addr);
}

/**
 * This is called for each read request we receive, never put more than one byte of data (with TinyWireS.send) to the
 * send-buffer when using this callback
 */
void requestEvent()
{
  if (comm_state == CommunicationState::Confirm)
  {
    TinyWireS.send(confirm_value);
    comm_state = CommunicationState::Data;
  } else {
    switch(current_op)
    {
      case Commands::GetRegister:
        TinyWireS.send(registers[register_query]);
        comm_state = CommunicationState::Idle;
        break;
      case Commands::GetOutput:
        {
          TinyWireS.send(output_registers[output_pointer]);
          ++output_pointer;
          if (output_pointer >= OUTPUT_REGISTER_COUNT)
          {
            comm_state = CommunicationState::Idle;
            output_pointer = 0;
          }
        }
        break;
      case Commands::GetVersion:
        TinyWireS.send(FW_VERSION);
        comm_state = CommunicationState::Idle;
        break;
      case Commands::Noop:
      case Commands::SetRegister:
      case Commands::SetOutput:
      case Commands::SetOutputIndex:
      default:
        comm_state = CommunicationState::Idle;
        break;
    }
  }
}

void shift_out_buffer()
{
  // We can't use the USI, since the I2C slave engadges it
  // Instead just shift out
  digitalWrite(SHIFT_LATCH_PIN, LOW);
  for(uint8_t i = 0; i < OUTPUT_REGISTER_COUNT; ++i)
  {
    shiftOut(SHIFT_DATA_PIN, SHIFT_CLK_PIN, MSBFIRST, output_registers[i]);
  }
  digitalWrite(SHIFT_LATCH_PIN, HIGH);
  registers[CONTROL_REGISTER_BUFFERSTATE] = BUFFERSTATE_CLEAN;
}

void SetError(uint8_t error_code)
{
  current_op = Commands::Noop;
  confirm_value = ERROR_FLAG | error_code;
}

void SetSuccess(uint8_t value)
{
  confirm_value = value & SUCCESS_MASK;
}

/**
 * The I2C data received -handler
 *
 * This needs to complete before the next incoming transaction (start, data, restart/stop) on the bus does
 * so be quick, set flags for long running tasks to be called from the mainloop instead of running them directly,
 */
void receiveEvent(uint8_t howMany)
{

    comm_state = CommunicationState::Idle;
    SetError(ErrorCode::UnknownOperation);
    if (howMany < 1)
    {
        return;
    }
    if (howMany > TWI_RX_BUFFER_SIZE)
    {
        return;
    }

    current_op = TinyWireS.receive();
    howMany--;
    comm_state = CommunicationState::Confirm;
    switch(current_op)
    {
      case Commands::SetRegister:
        // Byte 1: Register Index
        // Byte 2: Set Value
        if (howMany >= 2)
        {
          uint8_t reg_index = TinyWireS.receive();
          --howMany;
          uint8_t reg_value = TinyWireS.receive();
          --howMany;
          if (reg_index >= REGISTER_COUNT)
          {
            reg_index = 0;
            SetError(ErrorCode::InvalidIndex);
          } else {
            registers[reg_index] = reg_value;
            if (reg_index == CONTROL_REGISTER_I2C_ADDR)
            {
              write_i2c_addr(reg_value);
            }
            SetSuccess(reg_value);
          }
        } else {
          SetError(ErrorCode::InvalidDataSize);
        }
        break;
      case Commands::SetOutput:
        {
          if (howMany > 0
              && (output_pointer + howMany) < OUTPUT_REGISTER_COUNT)
          {
            registers[CONTROL_REGISTER_BUFFERSTATE] = BUFFERSTATE_DIRTY;
            while(howMany > 0)
            {
              output_registers[output_pointer] = TinyWireS.receive();
              --howMany;
              ++output_pointer;
            }
            if (output_pointer >= OUTPUT_REGISTER_COUNT)
            {
              output_pointer = 0;
            }
            SetSuccess(output_pointer);
          } else {
            SetError(ErrorCode::InvalidDataSize);
          }
        }
        break;
      case Commands::SetOutputIndex:
        {
          if (howMany == 1)
          {
            output_pointer = TinyWireS.receive();
            --howMany;
            if (output_pointer >= OUTPUT_REGISTER_COUNT)
            {
              output_pointer = 0;
              SetError(ErrorCode::InvalidIndex);
            }  else {
              SetSuccess(output_pointer);
            }
          } else {
            SetError(ErrorCode::InvalidDataSize);
          }
        }
        break;
      case Commands::GetRegister:
        {
          if (howMany == 1)
          {
            register_query = TinyWireS.receive();
            --howMany;
            if (register_query >= REGISTER_COUNT)
            {
              register_query = 0;
              SetError(ErrorCode::InvalidIndex);
            } else {
              SetSuccess(register_query);
            }
          } else {
            SetError(ErrorCode::InvalidDataSize);
          }
        }
        break;
      case Commands::GetOutput:
        {
          if ((howMany + output_pointer) > OUTPUT_REGISTER_COUNT)
          {
            SetError(ErrorCode::InvalidDataSize);
          }
        }
      case Commands::GetVersion:
      case Commands::Noop:
      default:
        SetSuccess(current_op);
        break;
    }
    // Drain the receive buffer
    while(howMany > 0)
    {
      TinyWireS.receive();
      --howMany;
    }
}

void setup()
{
    // TODO: Tri-state this and wait for input voltage to stabilize
    pinMode(SHIFT_LATCH_PIN, OUTPUT); // Connected to LATCH
    pinMode(SHIFT_CLK_PIN, OUTPUT); // OC1B-, Arduino pin 3, ADC, Connected to SHIFT CLK
    pinMode(SHIFT_DATA_PIN, OUTPUT);
    digitalWrite(SHIFT_LATCH_PIN, LOW); // Note that this makes the led turn on, it's wire this way to allow for the voltage sensing above.
    digitalWrite(SHIFT_CLK_PIN, LOW); // Note that this makes the led turn on, it's wire this way to allow for the voltage sensing above.
    digitalWrite(SHIFT_DATA_PIN, LOW);

    // Reset register ptr
    output_pointer = 0;

    uint8_t i2c_addr = read_i2c_addr();
    registers[CONTROL_REGISTER_I2C_ADDR] = DEFAULT_I2C_SLAVE_ADDRESS;
    // Valid address range is from 0x7F to 0x02
    if (i2c_addr > 0x7F
        || i2c_addr < 0x01)
    {
      write_i2c_addr(DEFAULT_I2C_SLAVE_ADDRESS);
    } else {
      registers[CONTROL_REGISTER_I2C_ADDR] = i2c_addr;
    }

    registers[CONTROL_REGISTER_MODE] = ControlMode::Demo;

    /**
     * Reminder: taking care of pull-ups is the masters job
     */

    TinyWireS.begin(registers[CONTROL_REGISTER_I2C_ADDR]);
    TinyWireS.onReceive(receiveEvent);
    TinyWireS.onRequest(requestEvent);
}

uint8_t demo_state = 0;
uint8_t demo_stop = 0;

void loop()
{
    /**
     * This is the only way we can detect stop condition (http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&p=984716&sid=82e9dc7299a8243b86cf7969dd41b5b5#984716)
     * it needs to be called in a very tight loop in order not to miss any (REMINDER: Do *not* use delay() anywhere, use tws_delay() instead).
     * It will call the function registered via TinyWireS.onReceive(); if there is data in the buffer on stop.
     */
    TinyWireS_stop_check();
    switch(registers[CONTROL_REGISTER_MODE])
    {
      case ControlMode::Demo:
        if (demo_stop < BYTE_TICK)
        {
          demo_stop = BYTE_TICK + 2;
          registers[CONTROL_REGISTER_BUFFERSTATE] = BUFFERSTATE_DIRTY;
          memset(reinterpret_cast<void*>(output_registers), 0, OUTPUT_REGISTER_COUNT);
          switch(demo_state)
          {
            case 0:
              demo_state = 1;
              output_registers[0] = 0xF0;
              break;
            case 1:
              demo_state = 0;
              output_registers[0] = 0x0F;
              break;
            default:
              break;
          }
        }
        break;
      case ControlMode::Slave:
        break;
      default:
        break;
    }
    if (registers[CONTROL_REGISTER_BUFFERSTATE] == BUFFERSTATE_DIRTY)
    {
      shift_out_buffer();
    }
}
