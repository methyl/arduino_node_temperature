#ifndef BlinkingDiode_h
#define BlinkingDiode_h

#include "Arduino.h"

class BlinkingDiode {
  public:
    BlinkingDiode(int, int);
    void start();
    void stop();

    void run();

  private:
    int pin, interval, lastTime;
    volatile bool isRunning;

    void turnOn();
    void turnOff();
    void toggle();
};

#endif
