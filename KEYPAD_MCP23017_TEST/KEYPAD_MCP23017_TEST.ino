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

uint8_t row_masks[] = {
  0x08, //ROW 1
  0x01, //ROW 2
  0x02, //ROW 3
  0x04, //ROW 4
};

uint8_t col_ports[] = {
  14, //COL 1
  15, //COL 2
  13, //COL 3
};

void setup() {
  // put your setup code here, to run once:
  mcp.begin();
  mcp.pinMode(8, INPUT);
  mcp.pinMode(9, INPUT);
  mcp.pinMode(10, INPUT);
  mcp.pinMode(11, INPUT);
  
  mcp.pinMode(13, OUTPUT);
  mcp.pinMode(14, OUTPUT);
  mcp.pinMode(15, OUTPUT);

  Serial.begin(115200);
}

void updateKey(int col, int row, uint8_t state) {
  if (keyStates[col][row] != ((state & row_masks[row]) != 0)) {
    keyStates[col][row] = ((state & row_masks[row]) != 0);
    if (keyStates[col][row] == true) {
      Serial.write(keys[col][row]);
      Serial.write('\n');
    }
  }
 }

void ScanCol(int col){
  mcp.digitalWrite(col_ports[col], HIGH);
  delay(20); //Debounce
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
