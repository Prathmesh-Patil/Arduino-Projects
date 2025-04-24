#include <Servo.h>

#define trigPin 8
#define echoPin 9
#define motorA1 2
#define motorA2 3
#define motorB1 4
#define motorB2 5
#define enableA 6
#define enableB 7
#define servoPin 10

Servo handServo;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(enableA, OUTPUT);
  pinMode(enableB, OUTPUT);
  handServo.attach(servoPin);
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  if (distance >= 2 && distance <= 30) {
    int servoAngle = map(distance, 2, 30, 0, 180);
    handServo.write(servoAngle);
    delay(50);
    moveRobotForward();
  } else {
    stopRobot();
  }
}

void moveRobotForward() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
  analogWrite(enableA, 255);
  analogWrite(enableB, 255);
}

void stopRobot() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
}
