#include <Wire.h>
#include "Adafruit_MCP23017.h"

#define GPIO_B 1

Adafruit_MCP23017 mcp;

char keys[3][4] = {
  {'1','4','7','*'},
  {'2','5','8','0'},
  {'3','6','9','#'}
};

bool keyStates[3][4] = {
  {false, false, false, false},
  {false, false, false, false},
  {false, false, false, false}
};

uint8_t row_ports[] = {
  0x0D, //TOP ROW 
  0x08, //MID HIGH ROW 
  0x09, //MID LOW ROW
  0x0B, //BOTTOM ROW
};

uint8_t col_ports[] = {
  0x0C, //LEFT COL
  0x0E, //MID COL
  0x0A, //RIGHT COL
};

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  delay(100);
  mcp.begin();
  mcp.pinMode(0, OUTPUT);
  mcp.digitalWrite(0, HIGH);
  for(int i = 0; i < 4; ++i) {
    mcp.pinMode(row_ports[i], INPUT);
  }

  for(int i = 0; i < 3; ++i) {
    mcp.pinMode(col_ports[i], OUTPUT);
  }
  
  Serial.begin(115200);
}

void updateKey(int col, int row, uint8_t state) {
  if (keyStates[col][row] != ((state & row_ports[row]) != 0)) {
    keyStates[col][row] = ((state & row_ports[row]) != 0);
    if (keyStates[col][row] == true) {
      Serial.write(keys[col][row]);
      Serial.write('\n');
    }
  }
 }

void ScanCol(int col){
  mcp.digitalWrite(col_ports[col], HIGH);
  delay(50); //Debounce
  uint8_t state = mcp.readGPIO(GPIO_B);
  mcp.digitalWrite(col_ports[col], LOW);

  for(int i = 0; i < 4; ++i) {
    updateKey(col, i, state);
  }
}

void ScanKeypad() {
  ScanCol(0);
  ScanCol(1);
  ScanCol(2);
}

void loop() {
  // put your main code here, to run repeatedly:
  ScanKeypad();
}
