
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac;

#define DAC_RESOLUTION (9)

void setup() {
  Serial.begin(9600);
  dac.begin(0x60);  // The I2C address of the MCP4725 DAC
}

void loop() {
  if (Serial.available()) {
    int value = Serial.parseInt();
    if (value >= 0 && value <= 4095) {
      dac.setVoltage(value, false);
    }
  }
}
