#include <Stepper.h>
#include <Servo.h>

int rsbReturn = 2;
int rsb = A1;
int rsbState = 0;
int state = 0;

int in1Pin = 12;
int in2Pin = 11;
int in3Pin = 10;
int in4Pin = 9;
int vsteps = 7700;

int vacuum = 8;
int sp = 7;
int sp1 = 6;
int sp2 = 5;
int sp3 = 4;
int sp4 = 3;

int c1 = A0;

int rsbPrc = 0;

#define STEPS 200
Stepper motor(STEPS, in1Pin, in2Pin, in3Pin, in4Pin);

Servo van;

void setup() {
  Serial.begin(9600);

  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
  pinMode(rsbReturn, OUTPUT);
  pinMode(rsb, INPUT);
  pinMode(vacuum, OUTPUT);
  pinMode(sp, OUTPUT);
  pinMode(sp1, OUTPUT);
  pinMode(sp2, OUTPUT);
  pinMode(sp3, OUTPUT);
  pinMode(sp4, OUTPUT);
  pinMode(c1, INPUT);

  digitalWrite(vacuum, HIGH);
  digitalWrite(sp, HIGH);
  digitalWrite(sp1, HIGH);
  digitalWrite(sp2, HIGH);
  digitalWrite(sp3, HIGH);
  digitalWrite(sp4, HIGH);

  motor.setSpeed(260);

  van.attach(13);
  closeVan();
}

void loop() {
  /*if (Serial.available()) {
    int s = Serial.parseInt();
    van.write(s);
    if (s == 1) {
      //upSpreader();
      inVacuum();
      //sequence();
    }
    if (s == 2) {
      outVacuum();
      //offVacuum();
      //downSpreader();
    }
    if (s == 3) {
      sequence();
    }
    if (s == 4) {
      upSpreader();
    }
    if (s == 5) {
      downSpreader();
      Serial.println(digitalRead(c1));
    }
    if (s == 6) {
      spread();
    }
  }*/
 if (digitalRead(rsb) == 1 && rsbPrc == 0) {
    cmd();
  }
  rsbPrc = digitalRead(rsb);

  Serial.println(digitalRead(rsb));
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
  downSpreader();
  openVan();
  delay(2000);
  closeVan();
  delay(1000);
  spread();
  upSpreader();
  delay(2000);
  inVacuum();
  onVacuum();
  delay(500);
  outVacuum();
  offVacuum();
}

void outVacuum() {
  motor.step(-vsteps);
  lowStepper();
}

void inVacuum() {
  motor.step(vsteps);
  lowStepper();
}

void onVacuum() {
  digitalWrite(vacuum, LOW);
}

void lowStepper() {
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, LOW);
    digitalWrite(in3Pin, LOW);
    digitalWrite(in4Pin, LOW);
}

void offVacuum() {
  digitalWrite(vacuum, HIGH);
}

void spread() {
  digitalWrite(sp, LOW);
  delay(1000);
  digitalWrite(sp, HIGH);
}

void upSpreader() {
  digitalWrite(sp1, LOW);
  digitalWrite(sp4, LOW);
  delay(5500);
  digitalWrite(sp1, HIGH);
  digitalWrite(sp4, HIGH);
}

void downSpreader() {
  if (digitalRead(c1) != 1) {
    digitalWrite(sp2, LOW);
    digitalWrite(sp3, LOW);
    while (digitalRead(c1) != 1);
    //delay(1500);
    digitalWrite(sp2, HIGH);
    digitalWrite(sp3, HIGH);
  }
}

void openVan () {
  van.write(22);
}

void closeVan () {
  van.write(75);
}
