const int ledPin = 11;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  Serial.begin(9600);
  Serial.setTimeout(100);
}

void loop() {
  char input[4];

  if (Serial.available() && Serial.read() == 'P') { // is there any data to read and first byte is P
    Serial.readBytes(input, 3);

    int pwmValue = atoi(input);
    analogWrite(ledPin, pwmValue);
  }
}
