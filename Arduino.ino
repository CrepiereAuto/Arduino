int rsbReturn = 2;
int rsb = 3;
int rsbState = 0;
int state = 0;

void setup() {
  Serial.begin(9600);
  pinMode(rsbReturn, OUTPUT);
  pinMode(rsb, INPUT);
  attachInterrupt(digitalPinToInterrupt(rsb), cmd, RISING);
}

void loop() {
  if (state) {
    digitalWrite(rsbReturn, HIGH);
    sequence();
    state = 0;
  } else {
    digitalWrite(rsbReturn, LOW);
  }
}

void cmd() {
  state = 1;
}

void sequence() {
  delay(5000);
}
