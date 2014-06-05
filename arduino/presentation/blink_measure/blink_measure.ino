#include "SimpleTimer.h"

const int ledPin = 11;
SimpleTimer timer;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // reset led state
  timer.setInterval(500, blink);
}

void loop() {
  timer.run();
}

void blink() {
  digitalWrite(ledPin, digitalRead(ledPin) ^ 1); // toggle pin status
}
