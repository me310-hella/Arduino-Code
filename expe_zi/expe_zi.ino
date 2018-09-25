#define FASTADC 1
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

const int LED_pin = 2;
const int fan_pin = 8;
const int fan_nullPin = 9; //Always set it to be 0v
const int s1_pin = A0;
const int s2_pin = A1;
const int s3_pin = A2;
const int s4_pin = A3;
const int s5_pin = A4;
const int s6_pin = A5;
const int s7_pin = A8;
const int s8_pin = A9; \


bool LED_state = false;
int screen_id = 0;
double s1, s2, s3, s4, s5, s6;
int s1raw, s2raw, s3raw, s4raw, s5raw, s6raw, s7raw, s8raw;
double t1, t2, t3, t4, t5, t6, t7, t8;
int s1max = 0, s2max = 0, s3max = 0, s4max = 0, s5max = 0, s6max = 0, s7max = 0, s8max = 0;
bool listen = false;
bool listen2 = false;
unsigned long listenTimer = 0;
unsigned long listenTimer2 = 0;

double up, mid, down, left, right;
int dataSend = -1;
int fanSpeed = 0;

void setup() {
 Serial.begin(9600);
 t1 = 300;
 t2 = 300;
 t3 = 300;
 t4 = 300;
 t5 = 300;
 t6 = 300;
 t7 = 144000;
 t8 = 300;
 pinMode(LED_pin, OUTPUT);
 digitalWrite(LED_pin, LOW);
 pinMode(fan_pin, OUTPUT);
 pinMode(fan_nullPin, OUTPUT);
 analogWrite(fan_pin, HIGH);
 analogWrite(fan_nullPin, LOW);
 //delay(5000);
}

void loop() {
 s1raw = analogRead(s1_pin);
 s2raw = 0;
 s3raw = analogRead(s3_pin);
 s4raw = analogRead(s4_pin);
 s5raw = analogRead(s5_pin);
 s6raw = analogRead(s6_pin);
 s7raw = 0;
 s8raw = analogRead(s8_pin);
 s1 = s1raw * 2.7;
 s2 = s2raw * 0.8;
 s3 = s3raw * 0.75;
 s4 = s4raw * 1.08;
 s5 = s5raw * 1;
 s6 = s6raw * 1.2;

 if ((s1 > t1 || s2 > t2 || s3 > t3 || s4 > t4 || s5 > t5 || s6 > t6) && !listen) {
   listenTimer = millis();
   listen = true;
 }

 if ((s7raw > t7 || s8raw > t8) && !listen2) {
   listenTimer2 = millis();
   listen2 = true;
 }

 if (listen2) {
   s7max = max(s7raw, s7max);
   s8max = max(s8raw, s8max);
   if (millis() > listenTimer2 + 300) {
     listen2 = false;
     if (s7max > s8max) {
       Serial.println("7");
     }
     else {
       Serial.println("8");
       if (fanSpeed > 0) {
         fanSpeed = 0;
         analogWrite(fan_pin, fanSpeed);
       }
       else {
         fanSpeed = 3;
         analogWrite(fan_pin, 80 * fanSpeed);
       }
     }
     s7max = 0;
     s8max = 0;
   }
 }

 if (listen) {
   s1max = max(s1, s1max);
   s2max = max(s2, s2max);
   s3max = max(s3, s3max);
   s4max = max(s4, s4max);
   s5max = max(s5, s5max);
   s6max = max(s6, s6max);
   //listen = millis() < listenTimer + 100;

   if (millis() > listenTimer + 300) {
     outputData(s1max, s2max, s3max, s4max, s5max, s6max);
     listen = false;
     up = s1max + s2max;
     mid = s3max + s4max;
     down = s5max + s6max;
     left = s1max + s3max + s5max;
     right = s2max + s4max + s6max;
     double maxVal = max(max(max(s1max, s2max), max(s3max, s4max)), max(s5max, s6max));
     int control = -1;
     if (s3max == max(s3max, s4max)) {
       if (s1max + s2max > s5max + s6max) {
         control = 1;
       }
       else control = 5;
     }
     else {
       if (s1max + s2max > s5max + s6max) {
         control = 2;
       }
       else control = 6;
     }
     /*
     left = s1max + s3max + s5max;
     right = s2max + s4max + s6max;
     if (s1max == maxVal) {
       Serial.println("1");
     }
     if (s2max == maxVal) {
       Serial.println("2");
     }
     if (s3max == maxVal) {
       Serial.println("3");
     }
     if (s4max == maxVal) {
       Serial.println("4");
     }
     if (s5max == maxVal) {
       Serial.println("5");
     }
     if (s6max == maxVal) {
       Serial.println("6");
     }
     if (left == max(left, right)) {
       if (up == max(max(up, mid), down)) {
         Serial.println("1");
       }
     }
     if (left == max(left, right)) {
       if (mid == max(max(up, mid), down)) {
         Serial.println("3");
       }
     }
     if (left == max(left, right)) {
       if (down == max(max(up, mid), down)) {
         Serial.println("5");
       }
     }
     if (right == max(left, right)) {
       if (up == max(max(up, mid), down)) {
         Serial.println("2");
       }
     }
     if (right == max(left, right)) {
       if (mid == max(max(up, mid), down)) {
         Serial.println("4");
       }
     }
     if (right == max(left, right)) {
       if (down == max(max(up, mid), down)) {
         Serial.println("6");
       }
     }
     */
     s1max = 0;
     s2max = 0;
     s3max = 0;
     s4max = 0;
     s5max = 0;
     s6max = 0;
     actuate(screen_id, control);
   }
 }
}

void outputData (double v1, double v2, double v3, double v4, double v5, double v6) {
 Serial.print(v1);
 Serial.print(' ');
 Serial.print(v2);
 Serial.print(' ');
 Serial.print(v3);
 Serial.print(' ');
 Serial.print(v4);
 Serial.print(' ');
 Serial.print(v5);
 Serial.print(' ');
 Serial.println(v6);
}

void actuate (int current_screen, int control) {
 control = 1;
 Serial.println(control);
 switch (current_screen) {
   case 0:
     switch (control) {
       case 1:
         LED_state = !LED_state;
         digitalWrite(LED_pin, LED_state);
         break;
       case 2:
         screen_id = 1; // AC
         break;
       case 4:
         screen_id = 2; // Navi
         break;
       case 5:
         screen_id = 3; // Music
         break;
       default:
         ;
     }
     break;
   case 1:
     switch (control) {
       case 1:
         fanSpeed = min(3, fanSpeed + 1);
         analogWrite(fan_pin, fanSpeed * 60);
         break;
       case 5:
         fanSpeed = max(0, fanSpeed - 1);
         analogWrite(fan_pin, fanSpeed * 60);
         break;
       default:
         screen_id = 0;
     }
     break;
   case 2:
     screen_id = 0;
     break;
   case 3:
     if (control < 3) screen_id = 0;
     break;
   default:
     ;
 }
}
