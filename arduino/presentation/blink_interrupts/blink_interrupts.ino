#include "TimerOne.h"

const int ledPin = 11;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // reset led state
  Timer1.initialize();
  Timer1.attachInterrupt(blink, 500 * 1000); // 500ms timeout
}

void loop() {}

void blink() {
  digitalWrite(ledPin, digitalRead(ledPin) ^ 1); // toggle pin status
}
