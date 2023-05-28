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



void setup() {
  for (int i = 0; i < sizeof(ledProperties) / sizeof(ledProperties[0]); i++) {
    pinMode(ledProperties[i].id, OUTPUT);
  }
}

void loop() {
  int id;
  for (int i = 0; i < sizeof(ledProperties) / sizeof(ledProperties[0]); i++) {
    id = ledProperties[i].id;
    ledBlink(ledProperties[i], 10);
  }
}

