#include "TemperatureSensor.h"

TemperatureSensor sensor(2); // setup sensor on pin 2

void setup() {
  sensor.start();
  Serial.begin(9600);
}

void loop() {
  if (sensor.updateTemperature()) {
    Serial.println(sensor.getTemperature());
  }
}
