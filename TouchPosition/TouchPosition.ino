#define FASTADC 1

//////////// Make the arduino faster //////////////
// defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif
////////////////////////////////////////////////

const int PIEZO_PIN_DR = A0; // Sensor Down right
const int PIEZO_PIN_UR = A2; // Sensor UP right
const int PIEZO_PIN_UL = A3; // Sensor UP left
const int PIEZO_PIN_DL = A1; // Sensor Down Left

long t1 = 0;
long t2 = 0;
long delta = 0;
int t1Sensor = -1;

int value_dr, value_dl;
int threshold = 1;
bool blocking = false;
long timeFrameStart;
long events[2];

void initTimeFrame(){
  //Serial.println("init time frame");
  timeFrameStart = millis();
  events[0] = 0L;
  events[1] = 0L;
  blocking = false;
}

void setup() {
  Serial.begin(9600);
  initTimeFrame();
}

int getPiezoValue(int analogValue){
  //return analogValue / 1023.0 * 100.0;
  return analogValue;
}

long getEventTime(int pin){
  if(analogRead(pin) > 0){
    return micros();
  }
  return 0;
}

void loop() {
  //Serial.print("Blocking: ");
  //Serial.println(blocking);
  
  if(millis() - timeFrameStart < 250L){
    if(events[0] == 0L){
      events[0] = getEventTime(PIEZO_PIN_DR);
    }
    if(events[1] == 0L){
      events[1] = getEventTime(PIEZO_PIN_DL);
    }
    if(events[0] != 0L && events[1] != 0L && !blocking){
      /*Serial.print(events[0]);
      Serial.print(":");
      Serial.println(events[1]);*/
      long delta = events[1] - events[0];
      Serial.println(delta);
      blocking = true;
    }
  } 
  else{
    initTimeFrame();
  }

}
