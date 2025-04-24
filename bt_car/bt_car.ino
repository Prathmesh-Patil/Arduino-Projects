#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // RX, TX for Bluetooth

// Motor pins
const int in1 = 2; // Motor 1 input pin 1
const int in2 = 3; // Motor 1 input pin 2
const int in3 = 4; // Motor 2 input pin 1
const int in4 = 5; // Motor 2 input pin 2

void setup() {
  // Initialize motor control pins
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  // Start serial communication
  Serial.begin(9600);
  BTSerial.begin(9600);
}

void loop() {
  if (BTSerial.available()) {
    String command = BTSerial.readStringUntil('\n');
    command.trim(); // Clean the command input

    if (command == "F" || command == "forward") {
      moveForward(); // Move both motors forward
      Serial.println("Moving forward");
    } 
    else if (command == "S" || command == "stop") {
      stopMotors(); // Stop both motors
      Serial.println("Motors stopped");
    }
    
    // Print the received command for debugging
    Serial.println("Received command: " + command);
  } 
  else {
    // If no command is received, stop the motors
    stopMotors(); // Ensure motors stop when no command is active
  }
}

// Function to move both motors forward
void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

// Function to stop both motors
void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
