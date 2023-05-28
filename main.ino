#include "Ultrasonic.h"

Ultrasonic ultrasonic(A0, A1);
int distance;

struct LedProperties {
  int id;
  int transitionDuration;
  int limit;
};

LedProperties ledProperties[] = {
  {11, 1, 255},  // ledRed
  {10, 1, 255},  // ledGreen
  {9, 1, 230},   // ledBlue
};

void ledOn(const LedProperties& led) {
  for (int bright = 0; bright < led.limit; bright++) {
    analogWrite(led.id, bright);
    delay(led.transitionDuration);
  }
}


void ledOff(const LedProperties& led) {
  for (int bright = led.limit; bright >= 0; bright--) {
    analogWrite(led.id, bright);  // Corrected the parameter to led.id
    delay(led.transitionDuration);
  }
}

void ledBlink(const LedProperties& led, int blinkTimes) {
  for (int i = 0; i <= blinkTimes; i++) {
    ledOn(led);
    delay(10);
    ledOff(led);
    delay(10);
  }
}

void allLedsOff(){
  for (int i = 0; i < sizeof(ledProperties) / sizeof(ledProperties[0]); i++) {
    digitalWrite(ledProperties[i].id, LOW);
  }
}

void setup() {
  for (int i = 0; i < sizeof(ledProperties) / sizeof(ledProperties[0]); i++) {
    pinMode(ledProperties[i].id, OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  distance = ultrasonic.Ranging(CM);
  if (distance >= 50 && distance <150){
    allLedsOff();
    ledOn(ledProperties[2]);
  } else if (distance >= 20){
    allLedsOff();
    ledOn(ledProperties[1]);
  } else if (distance <= 20) {
    allLedsOff();
    ledOn(ledProperties[0]);
  } else {
    allLedsOff();
  }
}

