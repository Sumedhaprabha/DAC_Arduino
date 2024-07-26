#include <Adafruit_MCP3008.h>
#include <SPI.h>

const int chipSelectPin1 = 10;
const int chipSelectPin2 = 9;
const int chipSelectPin3 = 8;
const int chipSelectPin4 = 7;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  pinMode(chipSelectPin1, OUTPUT);
  digitalWrite(chipSelectPin1, HIGH);  //Immediately set CS (slave select) high so the ADC isn't selected on startup.
  pinMode(chipSelectPin2, OUTPUT);
  digitalWrite(chipSelectPin2, HIGH);
  pinMode(chipSelectPin3, OUTPUT);
  digitalWrite(chipSelectPin3, HIGH);
  pinMode(chipSelectPin4, OUTPUT);
  digitalWrite(chipSelectPin4, HIGH);
}

void loop() {
  float reading1 = readADC(0, chipSelectPin1);
  float ADC1= convert(reading1);
  print_adc(ADC1,1, reading1);
  // float reading2 = readADC(0, chipSelectPin2);
  // float ADC2= convert(reading2);
  // print_adc(ADC2,2, reading2);
  // float reading3 = readADC(0, chipSelectPin3);
  // float ADC3= convert(reading3);
  // print_adc(ADC3, 3, reading3);
  // float reading4 = readADC(0, chipSelectPin4);
  // float ADC4= convert(reading4);
  // print_adc(ADC4, 4, reading4);
}

int readADC(byte channel, int chipSelectPin){
  byte startBit = 0b00000001;
  byte controlByte = 0b10000000; // First bit 1 gives us single-ended mode on ADC; the next three bits represent the ADC's analog input
  byte flushByte = 0b00000000; // Flush the ADC to get the remaining byte output.
  
  digitalWrite(chipSelectPin, LOW); //Initiate SPI protocol by dropping slave select low.
  SPI.transfer(startBit); // Fire off our start bit.
  byte readingH = SPI.transfer(controlByte);  // Push in our control byte which tells the ADC what mode to use and what channel we want.
  byte readingL = SPI.transfer(flushByte);  // Get the rest of our output from the ADC by flushing it with a byte of 0s.
  digitalWrite(chipSelectPin, HIGH);  // After flushing, immediately deselect the chip so that it doesn't continue.

  float reading = ((readingH & 0b00000011) << 8) + (readingL); // Per datasheet, we know that only the last two bits of our first transfer contain useful info. The second byte is all useful.
 return reading;
}

void print_adc(float ADC1, int n, float reading){
  // Serial.print("ADC");
  // Serial.print(n);
  // Serial.print(": ");
  Serial.println(ADC1);
  // Serial.print(",");
  // Serial.println(reading);
  delay(500);
}

float convert(float reading){
  return (reading*(5.0 /1023));
}

