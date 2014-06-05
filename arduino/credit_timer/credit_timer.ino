#include "CoinTimer.cpp"

CoinTimer timer;
bool impulse;

void setup() {
  pinMode(2, INPUT_PULLUP);
  Serial.begin(9600);
  Timer1.initialize();
  Timer1.attachInterrupt(onTick, 500000);
  // attachInterrupt(0, addCredit, FALLING);
  attachInterrupt(1, start, RISING);
}

void loop() {
  int r = digitalRead(2);
  if (r == 0) {
    impulse = true;
  }
  else if (impulse) {
    addCredit();
    impulse = false;
  }
}

void start() {
  timer.start();
}

void addCredit() {
  timer.addCredit();
}

void onTick() {
  Serial.print("Time left: ");
  Serial.println(timer.getTimeLeft());
  timer.onTick();
}
