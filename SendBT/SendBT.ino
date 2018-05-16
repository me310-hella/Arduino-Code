#include <SoftwareSerial.h>

SoftwareSerial BTSerial(0, 1); // RX | TX //10,11
int sensorPin = A0;
int sensorValue = 0;

void setup() 
{
  //String name = String("AT+NAME=ArduinoBT\r\n"); //Setting name as 'ArduinoBT'
  Serial.begin(9600);
  BTSerial.begin(9600);
  delay(500);
  while (BTSerial.available())
  {
    Serial.write(BTSerial.read());
  }
  //TSerial.print(setName); //Send Command to change the name
}

void loop() 
{
//IMPORTANT: The complete String has to be of the Form: 1234,1234,1234,1234;
//(every Value has to be seperated through a comma (',') and the message has to
//end with a semikolon (';'))



/*BTSerial.print("1");
BTSerial.print(",");
BTSerial.print("2");
//BTSerial.print(";");

//message to the receiving device

delay(20);*/

}
