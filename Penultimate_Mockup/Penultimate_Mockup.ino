#include <SoftwareSerial.h>

SoftwareSerial BTSerial(0, 1); // RX | TX //10,11
const int sensorPinLeft = A1; // Pin where you plug the sensor in
const int sensorPinRight = A0; // Pin where you plug the sensor in
int sensorValueLeft = 0;
int sensorValueRight = 0;

const int THRESHOLD = 150; // You have to adjust this threshold according to what signals come out of the sensor

void setup() 
{
  //String name = String("AT+NAME=ArduinoBT\r\n"); //Setting name as 'ArduinoBT'
  Serial.begin(9600);
  BTSerial.begin(9600);
  delay(500);
  /*while (BTSerial.available())
  {
    Serial.write(BTSerial.read());
  }*/
  //TSerial.print(setName); //Send Command to change the name
}

void loop() 
{
//IMPORTANT: The complete String has to be of the Form: 1234,1234,1234,1234;
//(every Value has to be seperated through a comma (',') and the message has to
//end with a semikolon (';'))

sensorValueLeft = analogRead(sensorPinLeft);
sensorValueRight = analogRead(sensorPinRight);

if(sensorValueLeft > THRESHOLD || sensorValueRight > THRESHOLD){
  if(sensorValueLeft > sensorValueRight){
    Serial.print("next\n");
  }
  else {
     Serial.print("prev\n");
  }

  //Serial.println(sensorValue);
  //Serial.print("prev\n");
  /*BTSerial.print("1");
  BTSerial.print(",");
  BTSerial.print("1");
  BTSerial.print("\n");*/
  delay(500);
}

//message to the receiving device

/*void send(char* data){
  
}*/

//delay(1000);
}
