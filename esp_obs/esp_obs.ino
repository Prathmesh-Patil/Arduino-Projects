#include <Servo.h>

// Motor A
int motorA1 = 12; // IN1 on the L298N
int motorA2 = 14; // IN2 on the L298N

// Motor B
int motorB1 = 4; // IN3 on the L298N
int motorB2 = 5; // IN4 on the L298N

// Ultrasonic Sensor
int trigPin = 16;
int echoPin = 17;
long duration, distance;

// Servo
Servo myservo;
int servoPin = 2;
int angle = 90; // servo position in degrees

void setup() {
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);

  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  myservo.attach(servoPin);
  myservo.write(angle);
  delay(2000); // wait for servo to reach the position

  Serial.begin(9600); // Starts the serial communication
}

void loop() {
  distance = measureDistance();
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > 20) {
    moveForward();
  } else {
    stopCar();
    lookAround();
  }
}

void moveForward() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}

void stopCar() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
}

long measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

void lookAround() {
  myservo.write(0); // Look left
  delay(1000);
  long distanceLeft = measureDistance();
  delay(100);
  myservo.write(180); // Look right
  delay(1000);
  long distanceRight = measureDistance();
  delay(100);
  myservo.write(90); // Return to center
  delay(1000);

  if (distanceLeft > distanceRight) {
    turnLeft();
  } else {
    turnRight();
  }
}

void turnLeft() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
  delay(500); // Adjust time based on your turn requirements
}

void turnRight() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
  delay(500); // Adjust time based on your turn requirements
}
