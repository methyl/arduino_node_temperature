#ifndef CreditBank_h
#define CreditBank_h

#include "Arduino.h"

class CreditBank {
public:
  CreditBank();

  void run();
  void start();
  void stop();
  void addCredits(int credits);

  int getSeconds();

private:
  static const int timeValue = 1;
  int lastTime;
  int seconds;
  int isRunning;
};

#endif
