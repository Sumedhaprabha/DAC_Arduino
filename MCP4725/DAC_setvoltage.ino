
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac;
// Set this value to 9, 8, 7, 6 or 5 to adjust the resolution
#define DAC_RESOLUTION (9)

void setup(void) {
  Serial.begin(9600);
  Serial.println("MCP4725A1 Test");

  // MCP4725A1 address is 0x62 (default) 
  // MCP4725A1 address is 0x63 (ADDR pin tied to VCC) 
  // MCP4725A1 address is 0x60 (ADDR pin tied to GND) 
  
  dac.begin(0x60);
}

void loop(void) {      

  //To check for the value entered in the serial monitor
  if(Serial.available())
  {
    //Input
      float Voltage = Serial.parseFloat();
      if(Voltage<=5.0 && Voltage>=0.0)
    {
      Serial.print("Voltage = "); Serial.print(Voltage); Serial.println(" V");

    //Setting voltage according to the characteristic equation
      dac.setVoltage((Voltage)/0.00122, false);      
      delay(1000);
      Serial.println("Enter next voltage");
    }
    else
    {
    //Error
      Serial.println("Error: Enter a value from 0 to 5");
    }
      

  }
}

/*
TO DO:
1. Check if the normal dac program is working - with multimeter - working (21/5/24 14:35)
2. Check if the given dac is working - get the address right - working (21/5/24 14:35)
3. Use the serial input program here and check for input vaules - working (21/5/24 15:54)
*/
