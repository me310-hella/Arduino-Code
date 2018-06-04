//#define FASTADC 1

//////////// Make the arduino faster //////////////
// defines for setting and clearing register bits
//#ifndef cbi
//#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
//#endif
//#ifndef sbi
//#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
//#endif
////////////////////////////////////////////////

//Sensors on the surface
///////
//A0  A1
//A2  A3
//A4  A5
///////

const int THRESHOLD = 0;
int sensorValues[] = {0,0,0,0,0,0};

void setup() {
  Serial.begin(9600);
}

void printValue(int value) {
  if (value > THRESHOLD) {
    Serial.println(value);
  }
}

int maxFromArray(int sensorValues[], int arrayLength){
  int maxValue = 0;
  int maxIndex = -1;
  for (int i=0; i<arrayLength; i++){
    Serial.print(sensorValues[i]);
    Serial.print(",");
    
    //maxValue = max(maxValue, sensorValues[i]);
    if(sensorValues[i] > maxValue){
      maxValue = sensorValues[i];
      maxIndex = i;
    }
  }
  Serial.println();
  return maxIndex;
}

int readValue(int pin){
  int sensorValue = analogRead(pin);
  if(sensorValue > THRESHOLD){
    return sensorValue;
  }
  else return 0;
}

void loop() {
  //Serial.print(sensorValues[0]);
 //Serial.print(",");
 sensorValues[0] = readValue(A0);
 sensorValues[1]= readValue(A1);
 sensorValues[2] = readValue(A2);
 sensorValues[3] = readValue(A3);
 sensorValues[4] = readValue(A4);
 //sensorValues[5] = analogRead(A6);


int maxIndex = maxFromArray(sensorValues, 5);
/*if(maxIndex > -1){
  Serial.println(maxIndex);   
}*/


//  printValue(sensorValue_5);
 
// Serial.print(sensorValue_0);
// Serial.print(",");
// Serial.print(sensorValue_1);
// Serial.print(",");
// Serial.print(sensorValue_2);
// Serial.print(",");
// Serial.print(sensorValue_3);
// Serial.print(",");
// Serial.print(sensorValue_4);
// Serial.print(",");
// Serial.print(sensorValue_5);
// Serial.println();
 //delay(500);
 delay(250);

}
