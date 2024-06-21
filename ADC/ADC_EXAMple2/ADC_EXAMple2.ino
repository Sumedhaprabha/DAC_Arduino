// This sketch demonstrates the use of the Gobetwino commandtypes LGFIL and CPFIL

#include <SPI.h>


#define SELPIN1 53 //Selection Pin 
#define SELPIN2 54
#define SELPIN3 55
#define SELPIN4 56
#define adc 4 
#define DATAOUT 51//MOSI 
#define DATAIN  50//MISO 
#define SPICLOCK  52//Clock  
int readvalue; 
byte clr;

int serInLen = 25;
char serInString[25];
int logValue1=0;
int logValue2=0;
int logValue3=0;
int logValue4=0;
int logValue5=0;
int logValue6=0;
int logValue7=0;
int logValue8=0;
int result;

void setup() 
{ 
 pinMode(SELPIN1, OUTPUT);
 pinMode(SELPIN2, OUTPUT); 
 pinMode(SELPIN3, OUTPUT);  
 pinMode(SELPIN4, OUTPUT); 
 pinMode(DATAOUT, OUTPUT); 
 pinMode(DATAIN, INPUT); 
 pinMode(SPICLOCK, OUTPUT); 
 //disable device to start with 
 digitalWrite(SELPIN1,HIGH); 
 digitalWrite(SELPIN2,HIGH);
 digitalWrite(SELPIN3,HIGH);
 digitalWrite(SELPIN4,HIGH);
 digitalWrite(DATAOUT,LOW); 
 digitalWrite(SPICLOCK,LOW);
  
  // Setup serial comm. Initialize random function.
  Serial.begin(9600); 
  //randomSeed(analogRead(0));
 // delay(5000); 
  // Use the CPTEST copy file command to make a copy of a new empty logfile
  Serial.println("#S|CPTEST|[]#");
  readSerialString(serInString,1000);
  // There ought to be a check here for a non 0 return value indicating an error and some error handeling
} 
 
void loop() 
{ 
   //Create some random values to log to a file on the PC.  This could be sensor readings or whatever
   //but for this example it's just 3 random values
   for(int i = 0; i < adc; i++ ){
   logValue1= read_adc(1,i+SELPIN1);
   logValue2= read_adc(2,i+SELPIN1);
   logValue3= read_adc(3,i+SELPIN1);
   logValue4= read_adc(4,i+SELPIN1);
   logValue5= read_adc(5,i+SELPIN1);
   logValue6= read_adc(6,i+SELPIN1);
   logValue7= read_adc(7,i+SELPIN1);
   logValue8= read_adc(8,i+SELPIN1);
   
   logData(logValue1,logValue2,logValue3,logValue4,logValue5,logValue6,logValue7,logValue8,i);
   delay(500); 
   }
}


//read a string from the serial and store it in an array
//you must supply the array variable - return if timeOut ms passes before the sting is read
void readSerialString (char *strArray,long timeOut) 
{
   long startTime=millis();
   int i;

   while (!Serial.available()) {
      if (millis()-startTime >= timeOut) {
         return;
      }
   }
   while (Serial.available() && i < serInLen) {
      strArray[i] = Serial.read();
      i++;
   }
}


int read_adc(int channel,int SELPIN) //function prototype for Read ADC
{  
  int adcvalue = 0;
  
  byte commandbits = B11000000; //command bits - start (B7) , mode (B6), channel (B3 to B5), dont care (B0 to B2)  Note: B1 (1st bit // LSB) ; B7 (8th bit //MSB)  (Channel refer to datasheet)
  
  //allow channel selection
  commandbits|=((channel-1)<<3); // must put "|" (not one "1" symbol) 
  
  digitalWrite(SELPIN,LOW); //Select adc
  // setup bits to be written
  for (int i=7; i>=3; i--){
   digitalWrite(DATAOUT,commandbits&1<<i);  // correct instruction  Note: it means commandbits & (1<<i), do "1<<i" first. 
   //digitalWrite(DATAOUT,HIGH); //cannot use this instruction
    
    //cycle clock
    digitalWrite(SPICLOCK,HIGH);
    digitalWrite(SPICLOCK,LOW);    
  }

  digitalWrite(SPICLOCK,HIGH);    //ignores 2 null bits
  digitalWrite(SPICLOCK,LOW);
  digitalWrite(SPICLOCK,HIGH);  
  digitalWrite(SPICLOCK,LOW);

  //read bits from adc since it is ADC is 10 bits, then int i=9; i>=0; i-- ; if ADC is 12 bits, then nt i=11; i>=0; i--
  for (int i=9; i>=0; i--){
    adcvalue+=digitalRead(DATAIN)<<i;
    
    //cycle clock
    digitalWrite(SPICLOCK,HIGH);
    digitalWrite(SPICLOCK,LOW);
  }
  digitalWrite(SELPIN, HIGH); //turn off device
  return adcvalue;
}

// Send the LOGTEST command to Gobetwino the 3 random values are seperated by semicolons
 
void logData( int value1, int value2, int value3, int value4, int value5, int value6, int value7, int value8, int num_adc) 
{
   char buffer[5];
  
   Serial.print("#S|LOGTEST|[");
   Serial.print(itoa((num_adc),buffer, 10));
   Serial.print(", ");
   Serial.print(itoa((value1), buffer, 10));
   Serial.print(", ");
   Serial.print(itoa((value2), buffer, 10));
   Serial.print(", ");
   Serial.print(itoa((value3), buffer, 10));
   Serial.print(", ");
   Serial.print(itoa((value4), buffer, 10));
   Serial.print(", ");
   Serial.print(itoa((value5), buffer, 10));
   Serial.print(", ");
   Serial.print(itoa((value6), buffer, 10));
   Serial.print(", ");
   Serial.print(itoa((value7), buffer, 10));
   Serial.print(", ");
   Serial.print(itoa((value8), buffer, 10));
   Serial.println("]#");
   readSerialString(serInString,1000);
   // There ought to be a check here for a non 0 return value indicating an error and some error handeling
} 
