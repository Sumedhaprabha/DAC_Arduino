  /*

  A sketch to control the 10-Bit, 8-channel ADC MCP3008 on the Rheingold Heavy
  I2C and SPI Education Shield.  The code supposes the use of the Education Shield,
  but if you're using a breakout board, connect the CS pin to Digital 4, and the
  SPI pins in their usual locations.

  Website:   https://rheingoldheavy.com/mcp3008-tutorial-02-sampling-dc-voltage/
  Datasheet: http://ww1.microchip.com/downloads/en/DeviceDoc/21295d.pdf


 */


#include <SPI.h>                         // Include the SPI library

SPISettings MCP3008(2000000, MSBFIRST, SPI_MODE0);

const int  CS_MCP3008       = 4;          // ADC Chip Select
const byte adc_single_ch0   = (0x08);     // ADC Channel 0
const byte adc_single_ch1   = (0x09);     // ADC Channel 1
const byte adc_single_ch2   = (0x0A);     // ADC Channel 2
const byte adc_single_ch3   = (0x0B);     // ADC Channel 3
const byte adc_single_ch4   = (0x0C);     // ADC Channel 4
const byte adc_single_ch5   = (0x0D);     // ADC Channel 5
const byte adc_single_ch6   = (0x0E);     // ADC Channel 6
const byte adc_single_ch7   = (0x0F);     // ADC Channel 7

void setup()
{
  Serial.pirntln ("Select ADC CS(0/1/2/3)");
  while(!Serial.available());
  int ADC_CS_SEL= Serial.readString().toInt();
  Serial.println (ADC_CS_SEL);
  
  switch (ADC_CS_SEL){
    case 0:
     chip_sc(CS_ADC0);
     break;
    case 1:
     chip_sc(CAS_ADC1);
     break;
    case 2:
     chip_sc(CS_ADC2);
     break;
    case 3:
     chip_sc(CAS_ADC3);
     break;
  }

  SPI.begin     ();
  Serial.begin  (9600);
  pinMode       (CS_MCP3008, OUTPUT);
  digitalWrite  (CS_MCP3008, LOW);        // Cycle the ADC CS pin as per datasheet
  digitalWrite  (CS_MCP3008, HIGH);

}



void loop()
{

  
  double vRef        = 3.75;
  int    adc_reading = 0;

  adc_reading        = adc_single_channel_read (adc_single_ch7);

  Serial.print       ("ADC Ch ");
  Serial.print       (adc_single_ch7 & 0x07);
  Serial.print       (" Voltage: ");
  Serial.println     ((adc_reading * vRef) / 1024, 2);

  delay(50);
  
}


int adc_single_channel_read(byte readAddress)
{

  byte dataMSB =    0;
  byte dataLSB =    0;
  byte JUNK    = 0x00;
  
  SPI.beginTransaction (MCP3008);
  digitalWrite         (CS_MCP3008, LOW);
  SPI.transfer         (0x01);                                 // Start Bit
  dataMSB =            SPI.transfer(readAddress << 4) & 0x03;  // Send readAddress and receive MSB data, masked to two bits
  dataLSB =            SPI.transfer(JUNK);                     // Push junk data and get LSB byte return
  digitalWrite         (CS_MCP3008, HIGH);
  SPI.endTransaction   ();

  return               dataMSB << 8 | dataLSB;

}