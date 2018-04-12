/*
* Bluetooh Basic: LED ON OFF - Avishkar
* Coder - Mayoogh Girish
* Website - http://bit.do/Avishkar
* Download the App : https://github.com/Mayoogh/Arduino-Bluetooth-Basic
* This program lets you to control a LED on pin 13 of arduino using a bluetooth module
*/
char data = 0;            //Variable for storing received data
int LED_PIN = 7;

void toggleLED()
{
  if(digitalRead(LED_PIN) == HIGH){
    digitalWrite(LED_PIN, LOW);
  }
  else { digitalWrite(LED_PIN, HIGH); }
}

void setup()
{
    Serial.begin(9600);   //Sets the baud for serial data transmission                               
    pinMode(LED_PIN, OUTPUT);  //Sets digital pin 7 as output pin

}
void loop()
{
   if(Serial.available() > 0)      // Send data only when you receive data:
   {
      data = Serial.read();        //Read the incoming data & store into data
      Serial.write("0,0");          //Print Value inside data in Serial monitor
      Serial.write("\n");        
      if(strcmp(data, "1")){
        toggleLED();
      }
   }
}


