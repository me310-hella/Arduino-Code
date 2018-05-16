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

int threshold = 150;

void setup() {
 Serial.begin(9600);

}

void printValue(int value){
  if(value > threshold){
    Serial.println(value);
  }
}

void loop() {
  int value_dr = analogRead(A0);
  int value_dl = analogRead(A1);

  int threshold = 100;

  if(value_dr > threshold){
    if(value_dl > threshold){
    Serial.print(value_dl);
    Serial.print(";");
    Serial.println(value_dr);
    }
    
  }
}
