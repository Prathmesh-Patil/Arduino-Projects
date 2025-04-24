#include <Servo.h>

int trigPin = 7;
int echoPin = 6;

int in1 = 2;
int in2 = 3;
int in3 = 4;
int in4 = 5;

int servoPin = 8;

Servo servoMotor;

void setup() {
  Serial.begin(9600);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  servoMotor.attach(servoPin);
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
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  servoMotor.write(0);

  if (distance <= 10) {
    // If the distance is less than or equal to 10 cm
    moveStop();
    servoMotor.write(90);  // Turn servo to change direction
    delay(100);
    servoMotor.write(0);
    moveBackward();  // Move backward
    delay(500);
    moveStop();  // Optional: Stop after moving back
  } else {
    // If the distance is greater than 10 cm
    moveForward();
  }
}

void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void moveBackward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void moveStop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void moveRight() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
