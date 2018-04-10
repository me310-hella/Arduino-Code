/*
* Bluetooh Basic: LED ON OFF - Avishkar
* Coder - Mayoogh Girish
* Website - http://bit.do/Avishkar
* Download the App : https://github.com/Mayoogh/Arduino-Bluetooth-Basic
* This program lets you to control a LED on pin 13 of arduino using a bluetooth module
*/
char data = 0;            //Variable for storing received data

void toggleLED()
{
  if(digitalRead(7) == HIGH){
    digitalWrite(7, LOW);
  }
  else { digitalWrite(7, HIGH); }
}

void setup()
{
    Serial.begin(9600);   //Sets the baud for serial data transmission                               
    pinMode(7, OUTPUT);  //Sets digital pin 7 as output pin
}
void loop()
{
   if(Serial.available() > 0)      // Send data only when you receive data:
   {
      data = Serial.read();        //Read the incoming data & store into data
      Serial.print(data);          //Print Value inside data in Serial monitor
      Serial.print("\n");        
      if(data == '1'){
        toggleLED();
      }
   }
}


