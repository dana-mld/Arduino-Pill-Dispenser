#include <Wire.h>
#include <Adafruit_PCF8574.h>
#include <SoftwareWire.h>
#include <RtcDS3231.h>
#include <Servo.h>

SoftwareWire rtcWire(A0, A1);
RtcDS3231<SoftwareWire> rtc(rtcWire);

Adafruit_PCF8574 pcf;

#define SEG_A 3
#define SEG_F 13
#define SEG_E 8
#define D3    2

// PCF 
#define SEG_B 2
#define SEG_C 5
#define SEG_D 7
#define SEG_G 4
#define SEG_DP 6
#define D1 0
#define D2 1
#define D4 3

Servo myservo;
#define SERVO_PIN 4

#define STEPPER_PIN_1 9
#define STEPPER_PIN_2 10
#define STEPPER_PIN_3 11
#define STEPPER_PIN_4 12

#define BUZZER_PIN 5
#define LED_PIN 7
#define BUTTON_PIN 6

int step_number = 0;

const int MORNING_HOUR = 15;
const int MORNING_MIN  =8;

const int EVENING_HOUR = 15;
const int EVENING_MIN  = 9;
const int RESET_HOUR  = 0;
const int RESET_MIN  = 0;
bool morningDone = false;
bool eveningDone = false;
bool checkReset = false;



void setup() {
  //Serial.begin(9600);

  rtcWire.begin();
  rtc.Begin();

 // if (!rtc.IsDateTimeValid()) {
    rtc.SetDateTime(RtcDateTime(__DATE__, __TIME__));
 // }
Serial.begin(9600);
Serial.println("BOOT");

  pcf.begin(0x20, &Wire);

  pinMode(SEG_A, OUTPUT);
  pinMode(SEG_F, OUTPUT);
  pinMode(SEG_E, OUTPUT);
  pinMode(D3, OUTPUT);

  pcf.pinMode(SEG_B, OUTPUT);
  pcf.pinMode(SEG_C, OUTPUT);
  pcf.pinMode(SEG_D, OUTPUT);
  pcf.pinMode(SEG_G, OUTPUT);
  pcf.pinMode(SEG_DP, OUTPUT);
  pcf.pinMode(D1, OUTPUT);
  pcf.pinMode(D2, OUTPUT);
  pcf.pinMode(D4, OUTPUT);

  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  pinMode(STEPPER_PIN_3, OUTPUT);
  pinMode(STEPPER_PIN_4, OUTPUT);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  myservo.attach(SERVO_PIN);
 myservo.write(0);
}

void loop() {
  RtcDateTime now = rtc.GetDateTime();

  showTime(now.Hour(), now.Minute());
  
  
  if(morningDone==false){
     showTextPILL();

  showTextAT();
 
  showMorningSet();
  }
  else if (eveningDone == false){
   showTextPILL();

  showTextAT();
 
   showEveningSet();
  }


  
 
  // throwPills();
 // rotateCompartment();
//reset
  if (now.Hour() == RESET_HOUR && now.Minute() == RESET_MIN ) {
    morningDone = false;
    eveningDone = false;
 }

  if ( morningDone == false &&
      now.Hour() == MORNING_HOUR &&
      now.Minute() == MORNING_MIN) {

    rotateCompartment();
    alert();
   morningDone = true;
    
  }

  if ( eveningDone == false &&
      now.Hour() == EVENING_HOUR &&
      now.Minute() == EVENING_MIN) {

   
    throwPills();
    delay(60);
     alert();
        

     
    eveningDone = true;
  }
}


void turnOffAllSegments() {
  digitalWrite(SEG_A, LOW);
  digitalWrite(SEG_E, LOW);
  digitalWrite(SEG_F, LOW);
  pcf.digitalWrite(SEG_B, LOW);
  pcf.digitalWrite(SEG_C, LOW);
  pcf.digitalWrite(SEG_D, LOW);
  pcf.digitalWrite(SEG_G, LOW);
}
void showTime(int h, int m) {
  int d[4] = { h / 10, h % 10, m / 10, m % 10 };

  for (int i = 0; i < 60; i++) {
    showDigit(digit1, d[0]);
    showDigit(digit2, d[1]);
    showDigit(digit3, d[2]);
    showDigit(digit4, d[3]);
  }
}

void showDigit(void (*digit)(), int n) {
  turnOffAllSegments();
  digit();
  setNumber(n);
  delay(2);
}
void showP()
{
   //p
    turnOffAllSegments();
  digit1();
 digitalWrite(SEG_A, HIGH);
pcf.digitalWrite(SEG_B, HIGH);
pcf.digitalWrite(SEG_C, LOW);   
pcf.digitalWrite(SEG_D, LOW);   
digitalWrite(SEG_E, HIGH);        
digitalWrite(SEG_F, HIGH);
pcf.digitalWrite(SEG_G, HIGH);
  delay(2);
}

void showI()
{
   //I
      turnOffAllSegments();
    digit2();
 digitalWrite(SEG_A, LOW);
  pcf.digitalWrite(SEG_B, HIGH);
  pcf.digitalWrite(SEG_C, HIGH);
  pcf.digitalWrite(SEG_D, LOW);
  digitalWrite(SEG_E, LOW);
  digitalWrite(SEG_F, LOW);
  pcf.digitalWrite(SEG_G, LOW);
  delay(2);

}
void showL1()
{
     turnOffAllSegments();
  //L
    digit3();
 digitalWrite(SEG_A, LOW);
  pcf.digitalWrite(SEG_B, LOW);
  pcf.digitalWrite(SEG_C, LOW);
  pcf.digitalWrite(SEG_D, HIGH);
  digitalWrite(SEG_E, HIGH);
  digitalWrite(SEG_F, HIGH);
  pcf.digitalWrite(SEG_G, LOW);
  delay(2);
}
void showL2()
{
     turnOffAllSegments();
  //L
    digit4();
  digitalWrite(SEG_A, LOW);
  pcf.digitalWrite(SEG_B, LOW);
  pcf.digitalWrite(SEG_C, LOW);
  pcf.digitalWrite(SEG_D, HIGH);
  digitalWrite(SEG_E, HIGH);
  digitalWrite(SEG_F, HIGH);
  pcf.digitalWrite(SEG_G, LOW);
  delay(2);
}
void showA()
{
     //A
        turnOffAllSegments();
    digit1();
 digitalWrite(SEG_A, HIGH);
  pcf.digitalWrite(SEG_B, HIGH);
  pcf.digitalWrite(SEG_C, HIGH);
  pcf.digitalWrite(SEG_D, LOW);
  digitalWrite(SEG_E, HIGH);
  digitalWrite(SEG_F, HIGH);
  pcf.digitalWrite(SEG_G, HIGH);
  delay(2);
}
void showT()
{
     turnOffAllSegments();
  digit2();
 digitalWrite(SEG_A, HIGH);
  pcf.digitalWrite(SEG_B, LOW);
  pcf.digitalWrite(SEG_C, LOW);
  pcf.digitalWrite(SEG_D, LOW);
  digitalWrite(SEG_E, HIGH);
  digitalWrite(SEG_F, HIGH);
  pcf.digitalWrite(SEG_G, LOW);
  delay(2);
}
void showTextPILL() {
for (int i = 0; i < 60; i++) 
    {showP();   showI();   showL1();   showL2(); }
  
}
void showTextAT() {
  
  for (int i = 0; i < 60; i++) 
   { showA();showT(); }
  
}

void showMorningSet(){
 showTime(MORNING_HOUR, MORNING_MIN);
}
void showEveningSet(){
  showTime(EVENING_HOUR, EVENING_MIN);
}

void digit1() { pcf.digitalWrite(D1, LOW);  pcf.digitalWrite(D2, HIGH); digitalWrite(D3, HIGH); pcf.digitalWrite(D4, HIGH); }
void digit2() { pcf.digitalWrite(D1, HIGH); pcf.digitalWrite(D2, LOW);  digitalWrite(D3, HIGH); pcf.digitalWrite(D4, HIGH); }
void digit3() { pcf.digitalWrite(D1, HIGH); pcf.digitalWrite(D2, HIGH); digitalWrite(D3, LOW);  pcf.digitalWrite(D4, HIGH); }
void digit4() { pcf.digitalWrite(D1, HIGH); pcf.digitalWrite(D2, HIGH); digitalWrite(D3, HIGH); pcf.digitalWrite(D4, LOW); }
int pos = 0;
void setNumber(int n) {
  static const bool seg[10][7] = {
    {1,1,1,1,1,1,0}, {0,1,1,0,0,0,0}, {1,1,0,1,1,0,1},
    {1,1,1,1,0,0,1}, {0,1,1,0,0,1,1}, {1,0,1,1,0,1,1},
    {1,0,1,1,1,1,1}, {1,1,1,0,0,0,0}, {1,1,1,1,1,1,1},
    {1,1,1,1,0,1,1}
  };

  digitalWrite(SEG_A, seg[n][0]);
  pcf.digitalWrite(SEG_B, seg[n][1]);
  pcf.digitalWrite(SEG_C, seg[n][2]);
  pcf.digitalWrite(SEG_D, seg[n][3]);
  digitalWrite(SEG_E, seg[n][4]);
  digitalWrite(SEG_F, seg[n][5]);
  pcf.digitalWrite(SEG_G, seg[n][6]);
}

void disableDisplay() {
  turnOffAllSegments();
  pcf.digitalWrite(D1, HIGH);
  pcf.digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  pcf.digitalWrite(D4, HIGH);
}

void enableDisplay() {
}

void throwPills() {
  
  for (int pos = 0; pos <= 90; pos++) { 
    myservo.write(pos);              
    delay(6);                      
  }
  delay(100); 
  for (int pos = 90; pos >= 0; pos--) { 
    myservo.write(pos);             
    delay(6);                   
  }
  
}

void OneStep(bool dir) {
  static const byte seq[4][4] = {
    {1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}
  };
  int s = dir ? step_number : (3 - step_number);
  digitalWrite(STEPPER_PIN_1, seq[s][0]);
  digitalWrite(STEPPER_PIN_2, seq[s][1]);
  digitalWrite(STEPPER_PIN_3, seq[s][2]);
  digitalWrite(STEPPER_PIN_4, seq[s][3]);
  step_number = (step_number + 1) % 4;
}

void rotateCompartment() {
  
  for (int i = 0; i < 270; i++) {
    OneStep(false);
    delay(2);
  }
  
  
}
void alert() {
  digitalWrite(BUZZER_PIN, HIGH);
  digitalWrite(LED_PIN, HIGH);

  while (digitalRead(BUTTON_PIN) == HIGH);

  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
}
