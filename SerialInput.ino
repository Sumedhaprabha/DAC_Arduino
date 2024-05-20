

// void setup(void){
//   Serial.begin(9600);
//   Serial.println("Enter a value from 0 to 5");
// }

// void loop(void){

//   if(Serial.available())
//   {
//     float Voltage = Serial.parseFloat();

//     if(Voltage<=5.0 && Voltage>=0.0)
//     {
//       Serial.print("The voltage entered = "); Serial.println(Voltage); 
//     }
//     else
//     {
//       Serial.println("Error: Enter a value from 0 to 5");
//     }
//   }

// }// why is voltage going to 0.0 after every loop? - its because if the timeout is more than a second the serial monitor will assume the value 0- use newline or atoi

// /*
// 1. Get the input
// 2. Check if it is - else error message
//         - Within 0 to 5V
//         - Is a number 
//         - not negative - covered by the first condition
//         - no special characters 
// 3. Send it to dac for further process 
//  20/5/24 - 10:16  - Got the required output, tested with both integers and alphabets.
// */