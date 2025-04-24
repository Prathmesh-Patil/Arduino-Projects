#include <Servo.h>

// Ultrasonic sensor pins
const int trigPin = 7;
const int echoPin = 6;

// Motor driver input pins
const int in1 = 2;
const int in2 = 3;
const int in3 = 4;
const int in4 = 5;

// Motor driver enable pins
const int enA = 9;  // Enable pin for motors connected to in1 and in2
const int enB = 10; // Enable pin for motors connected to in3 and in4

// Servo motor pin
const int servoPin = 8;

// Servo motor object
Servo servoMotor;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set motor driver pins as outputs
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  // Initialize the motor speed to maximum
  analogWrite(enA, 255); // Set motor speed (0-255)
  analogWrite(enB, 255); // Set motor speed (0-255)

  // Set ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Attach servo motor to pin
  servoMotor.attach(servoPin);
}

void loop() {
  // Scan for obstacles and decide on the best movement strategy
  int bestDirection = scanForBestDirection();
  handleMovement(bestDirection);
}

// Function to scan for the best direction
int scanForBestDirection() {
  int bestAngle = 90;  // Default to forward
  int maxDistance = 0;
  for (int angle = 0; angle <= 180; angle += 30) {
    servoMotor.write(angle);
    delay(500); // Allow the servo to stabilize
    int distance = measureDistance();
    Serial.print("Angle: "); Serial.print(angle); Serial.print(" Distance: "); Serial.println(distance);
    if (distance > maxDistance) {
      maxDistance = distance;
      bestAngle = angle;
    }
  }
  servoMotor.write(90); // Reset servo position to forward after scanning
  return bestAngle;
}

// Function to measure distance
int measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 25000); // 25 ms timeout to prevent freezing
  if (duration == 0) {
    duration = 25000; // Consider out of range as max distance
  }
  return (duration / 2) / 29.1; // Convert time to distance
}

// Function to handle movement based on best angle
void handleMovement(int angle) {
  if (angle == 90) { // If best direction is forward
    moveForward();
  } else if (angle < 90) { // Turn left
    moveLeft();
    delay(1000); // Turn for 1 second
    moveForward();
  } else { // Turn right
    moveRight();
    delay(1000); // Turn for 1 second
    moveForward();
  }
}

// Movement control functions
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

void moveLeft() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
