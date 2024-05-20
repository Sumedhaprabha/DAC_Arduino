#include <Wire.h>
#include <Adafruit_MCP4725.h>
Adafruit_MCP4725 dac;
// Set this value to 9, 8, 7, 6 or 5 to adjust the resolution
#define DAC_RESOLUTION (9)

void setup(void) {
  Serial.begin(9600);
  Serial.println("MCP4725A1 Test");
  Serial.println("Enter the value of the voltage (from 0 to 5) : ");

  // MCP4725A1 address is 0x62 (default) 
  // MCP4725A1 address is 0x63 (ADDR pin tied to VCC) 
  // MCP4725A1 address is 0x60 (ADDR pin tied to GND) 
  dac.begin(0x60); //I have my ADDR pin connected to GND so address is 0x60
  Serial.println("Enter the value of the voltage (from 0 to 5) : ");

}

void loop(void) {      

  
  // if(Serial.available() > 0){

  //   float Voltage = Serial.parseFloat();
  //   if(Voltage<=5)
  //   {
  //     dac.setVoltage((Voltage*4095)/5, false);
  //     delay(2000);  
  //     Serial.print("Setting voltage to -- "); Serial.println(Voltage);
  //   }
  //   else
  //   Serial.println("Error: Enter a value between 0 to 5V");

  // } // To wait till the user enters input
  // else
  // {
  //   Serial.println("Enter the value of the voltage (from 0 to 5) : ");

  // }
    
  dac.setVoltage((1*4120)/5, false);        //Set voltage to 1V
  delay(2000);
  dac.setVoltage((2*4120)/5, false);        //Set voltage to 2V
  delay(2000);
  dac.setVoltage((3*4120/5), false);         //Set voltage to 3V
  delay(2000);
  dac.setVoltage((4*4120)/5, false);        //Set voltage to 4V
  delay(2000);
  dac.setVoltage(4095, false);              //Set voltage to 5V or (Vcc)
  delay(2000); 
}

/*
1. Check if the normal dac program is working - with multimeter
2. Check if the given dac is working - get the address right
3. use the serial input program here and check for input vaules
*/