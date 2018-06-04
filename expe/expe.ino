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


const int PINS[] = {A0, A1, A2, A3, A4, A5};
const int THRESHOLDS[] = {30, 30, 30, 30, 30, 30};
const int TIME_FRAME = 250;
int sensorValues[] = {0,0,0,0,0,0};
long start;

void setup() {
  Serial.begin(9600);
}

int maxFromArray(int sensorValues[], int arrayLength){
  int maxValue = 0;
  int maxIndex = -1;
  for (int i=0; i<arrayLength; i++){
    if(sensorValues[i] > maxValue){
      maxValue = sensorValues[i];
      maxIndex = i;
    }
  }
  return maxIndex;
}

int readValue(int readIndex){
  int threshold = THRESHOLDS[readIndex];
  int pin = PINS[readIndex];
  int sensorValue = analogRead(pin);
  if(sensorValue > threshold){
    return sensorValue;
  }
  else return 0;
}

void printArray(int values[], int length) {
  for (int i = 0; i < length; i ++) {
    Serial.print(values[i]);
    Serial.print(",");
  }
  Serial.println();
}

void initValues(int values[], int length) {
  for (int i = 0; i < length; i ++) {
    values[i] = 0;
  }
}

bool updateValues(int values[], int length) {
  bool changed = false;
  for (int i = 0; i < length; i ++) {
    int newValue = max(values[i], readValue(i));
    changed = newValue > 0;
    values[i] = newValue;
  }
  return changed;
}

void loop() {
 bool started = updateValues(sensorValues, 6);
 if (!started) {
  return;
 }
 start = millis();
 while (millis() - start < TIME_FRAME) {
  updateValues(sensorValues, 6);
 }
 printArray(sensorValues, 6);
 initValues(sensorValues, 6);
 start = millis();
}
