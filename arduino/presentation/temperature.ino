#include "TemperatureSensor.h"

const int ledPin = 11;
int pwmValue = 0;
char input[4];

TemperatureSensor sensor(2);
TemperatureSensor sensor2(3);

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  Serial.setTimeout(500);
  sensor.start();
  sensor2.start();
}

void loop() {
  if (Serial.available() && Serial.read() == 'P') { // is there any data to read and first byte is P
    Serial.readBytes(input, 4);

    pwmValue = atoi(input);
    analogWrite(ledPin, pwmValue);
  }

  if (sensor.updateTemperature()) {
    Serial.print("1: ");
    Serial.println(sensor.getTemperature());
  }

  if (sensor2.updateTemperature()) {
    Serial.print("2: ");
    Serial.println(sensor2.getTemperature());
  }
}

