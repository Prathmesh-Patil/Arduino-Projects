int a1 = 13;
int a2 = 12;
int b1 = 9;
int b2 = 10;

int IR_PIN = A4; // Assuming the IR sensor is connected to pin 4

void setup() {
  Serial.begin(9600);
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(IR_PIN, INPUT); // IR sensor pin set as input
}

String str;

void loop() {
  // Read IR sensor input
  int obstacleDetected = digitalRead(IR_PIN);
  
  // Check if obstacle is detected by IR sensor
  if (obstacleDetected == HIGH) { // Adjust as needed based on sensor behavior
    // Stop the motors if obstacle detected
    stopMotors();
  } else {
    // Proceed with the movement commands received from the Bluetooth module
    if (str == "forward") {
      moveForward();
    } else if (str == "backward") {
      moveBackward();
    } else if (str == "left") {
      turnLeft();
    } else if (str == "right") {
      turnRight();
    }
  }
  
  // Read command from Bluetooth
  if (Serial.available() > 0) {
    str = Serial.readStringUntil('\n'); // Read a line from serial
    Serial.println(str);
  }
}

void moveForward() {
  digitalWrite(a1, LOW);
  digitalWrite(a2, HIGH);
  digitalWrite(b1, LOW);
  digitalWrite(b2, HIGH);
}

void moveBackward() {
  digitalWrite(a1, HIGH);
  digitalWrite(a2, LOW);
  digitalWrite(b1, HIGH);
  digitalWrite(b2, LOW);
}

void turnLeft() {
  digitalWrite(a1, HIGH);
  digitalWrite(a2, LOW);
  digitalWrite(b1, LOW);
  digitalWrite(b2, HIGH);
}

void turnRight() {
  digitalWrite(a1, LOW);
  digitalWrite(a2, HIGH);
  digitalWrite(b1, HIGH);
  digitalWrite(b2, LOW);
}

void stopMotors() {
  digitalWrite(a1, LOW);
  digitalWrite(a2, LOW);
  digitalWrite(b1, LOW);
  digitalWrite(b2, LOW);
}
