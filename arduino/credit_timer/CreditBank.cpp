#include "CreditBank.h";

CreditBank::CreditBank() {
  seconds = 0;
  isRunning = false;
}

void CreditBank::run() {
  if (! isRunning) return;

  if (millis() - lastTime > 1000) {
    lastTime = millis();
    if(seconds == 0)
      stop();
    else
      seconds -= 1;
  }
}

void CreditBank::start() {
  isRunning = true;
}

void CreditBank::stop() {
  isRunning = false;
}

void CreditBank::addCredits(int credits) {
  seconds += credits * timeValue;
}

int CreditBank::getSeconds() {
  return seconds;
}
