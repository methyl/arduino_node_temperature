#include "BlinkingDiode.h";

BlinkingDiode::BlinkingDiode(int pin, int interval = 500) {
  this->pin = pin;
  this->interval = interval;
  isRunning = false;
  lastTime = 0;
}

void BlinkingDiode::start() {
  if (isRunning) { return; }
  isRunning = true;

}

void BlinkingDiode::stop() {
  if (!isRunning) { return; }
  isRunning = false;
  turnOff();
}

void BlinkingDiode::run() {
  if (! isRunning) { return; }
  if (millis() - lastTime > interval) {
    lastTime = millis();
    toggle();
  }
}

void BlinkingDiode::turnOn() {
  Serial.println("turning on");
  digitalWrite(pin, HIGH);
}

void BlinkingDiode::turnOff() {
  Serial.println("turning off");
  digitalWrite(pin, LOW);
}

void BlinkingDiode::toggle() {
  digitalWrite(pin, digitalRead(pin) ^ 1);
}
