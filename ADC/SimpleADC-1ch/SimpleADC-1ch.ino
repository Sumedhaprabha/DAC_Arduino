#include <Adafruit_MCP3008.h>

Adafruit_MCP3008 adc;

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("MCP3008 Test");
  adc.begin();
}

void loop() {
  int raw = adc.readADC(0);
  Serial.print(raw);
  Serial.print("\t");
  Serial.println(voltage(raw));
  delay(1000);
}

float voltage(int raw){
  return raw/1023.0 * 4.9;
}