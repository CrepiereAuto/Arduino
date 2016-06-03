#include <Stepper.h>

int rsbReturn = 2;
int rsb = 3;
int rsbState = 0;
int state = 0;
int in1Pin = 12;
int in2Pin = 11;
int in3Pin = 10;
int in4Pin = 9;
int vsteps = 8000;

#define STEPS 512
Stepper motor(STEPS, in1Pin, in2Pin, in3Pin, in4Pin);

void setup() {
  Serial.begin(9600);
  
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
  pinMode(rsbReturn, OUTPUT);
  pinMode(rsb, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(rsb), cmd, RISING);
  motor.setSpeed(60);
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

void outVacuum() {
    motor.step(vsteps);
}

void inVacuum() {
    motor.step(-vsteps);
}
