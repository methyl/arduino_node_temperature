#include "arduino.h"
#include "TimerOne.h"

class Relay {
  int pin;

public:

  Relay(int pin) {
    this->pin = pin;
    pinMode(pin, OUTPUT);
    turnOff();
  }

  void turnOn() {
    digitalWrite(pin, HIGH);
  }

  void turnOff() {
    digitalWrite(pin, LOW);
  }
};

class Diode {
  int pin;

public:

  Diode(int pin) {
    this->pin = pin;
    pinMode(pin, OUTPUT);
  }

  void turnOn() {
    digitalWrite(pin, HIGH);
  }

  void turnOff() {
    digitalWrite(pin, LOW);
  }

  void toggle() {
    digitalWrite(pin, digitalRead(pin) ^ 1);
  }

  void blink() {
    turnOn();
    delay(50);
    turnOff();
  }
};

class CoinTimer {
public:
  CoinTimer() : counterDiode(5), statusDiode(13), relay(7) {
    miliseconds = 0;
  }

  void start() {
    if (miliseconds > 0) {
      isRunning = true;
      relay.turnOn();
    }
  }

  void stop() {
    isRunning = false;
    relay.turnOff();
    counterDiode.turnOff();
  }

  void addCredit() {
    Serial.print("Added: ");
    Serial.println(creditValue);
    miliseconds += creditValue;
    statusDiode.blink();
    start();
  }

  unsigned long getTimeLeft() {
    return miliseconds / 1000;
  }

  void onTick() {
    if (!isRunning) return;

    if (miliseconds > 0) {
      miliseconds -= 500;
      if (miliseconds % 1000 == 0)
        counterDiode.turnOn();
      if (miliseconds % 1000 == 500)
        counterDiode.turnOff();
    } else {
      stop();
    }
  }

private:
  Diode counterDiode;
  Diode statusDiode;
  Relay relay;
  volatile unsigned long miliseconds;
  volatile bool isRunning;
  static const unsigned long creditValue = 4000L * 60L; // one credit = 2.5min
};
