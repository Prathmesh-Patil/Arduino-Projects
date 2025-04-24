#include <Servo.h>

Servo gateServo;  // Create a Servo object to control the servo motor
int irSensor = 2; // IR sensor connected to digital pin D2
int gatePosOpen = 0; // Position for the gate to be fully open
int gatePosClose = 60; // Position for the gate to be fully closed
int sensorState = 0;  // Variable to store IR sensor state
bool gateOpened = false; // Flag to track if the gate is open
unsigned long gateOpenTime = 0; // To track when the gate was opened

void setup() {
  gateServo.attach(9);   // Attach the servo motor to digital pin D9
  pinMode(irSensor, INPUT);  // Set the IR sensor pin as input
  gateServo.write(gatePosClose);  // Start with the gate in closed position
  Serial.begin(9600);  // Start serial communication for debugging (optional)
}

void loop() {
  sensorState = digitalRead(irSensor);  // Read the state of the IR sensor

  // If the IR sensor detects a vehicle (sensorState is LOW) and the gate is not already open
  if (sensorState == LOW && !gateOpened) {
    Serial.println("Vehicle detected! Opening gate...");
    gateServo.write(gatePosOpen);  // Open the gate
    gateOpened = true;  // Mark gate as open
    gateOpenTime = millis();  // Store the current time when the gate was opened
  }

  // Check if 10 seconds have passed since the gate was opened
  if (gateOpened && (millis() - gateOpenTime >= 5000)) {
    Serial.println("Closing gate after 10 seconds...");
    gateServo.write(gatePosClose);  // Close the gate
    gateOpened = false;  // Reset the gate status to closed
  }

  delay(100);  // Small delay to prevent excessive sensor reads
}
