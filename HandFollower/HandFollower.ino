#define LEFT_IR_PIN 2   // IR sensor on the left connected to pin 2
#define RIGHT_IR_PIN 3  // IR sensor on the right connected to pin 3

#define MOTOR1_PIN1 4   // Motor 1 input pin 1
#define MOTOR1_PIN2 5   // Motor 1 input pin 2
#define MOTOR2_PIN1 6   // Motor 2 input pin 1
#define MOTOR2_PIN2 7   // Motor 2 input pin 2

void setup() {
  pinMode(LEFT_IR_PIN, INPUT);
  pinMode(RIGHT_IR_PIN, INPUT);
  pinMode(MOTOR1_PIN1, OUTPUT);
  pinMode(MOTOR1_PIN2, OUTPUT);
  pinMode(MOTOR2_PIN1, OUTPUT);
  pinMode(MOTOR2_PIN2, OUTPUT);
}

void loop() {
  int leftIR = digitalRead(LEFT_IR_PIN);
  int rightIR = digitalRead(RIGHT_IR_PIN);

  if (leftIR == HIGH && rightIR == LOW) {
    // Turn or move left
    digitalWrite(MOTOR1_PIN1, LOW);
    digitalWrite(MOTOR1_PIN2, HIGH);
    digitalWrite(MOTOR2_PIN1, HIGH);
    digitalWrite(MOTOR2_PIN2, LOW);
  } else if (rightIR == HIGH && leftIR == LOW) {
    // Turn or move right
    digitalWrite(MOTOR1_PIN1, HIGH);
    digitalWrite(MOTOR1_PIN2, LOW);
    digitalWrite(MOTOR2_PIN1, LOW);
    digitalWrite(MOTOR2_PIN2, HIGH);
  } else if (rightIR == HIGH && leftIR == HIGH) {
    // Move forward
    digitalWrite(MOTOR1_PIN1, HIGH);
    digitalWrite(MOTOR1_PIN2, LOW);
    digitalWrite(MOTOR2_PIN1, HIGH);
    digitalWrite(MOTOR2_PIN2, LOW);
  } else {
    // Stop
    digitalWrite(MOTOR1_PIN1, LOW);
    digitalWrite(MOTOR1_PIN2, LOW);
    digitalWrite(MOTOR2_PIN1, LOW);
    digitalWrite(MOTOR2_PIN2, LOW);
  }
}
