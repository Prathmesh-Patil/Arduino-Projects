#include <SoftwareSerial.h>

// Create a SoftwareSerial object to communicate with HC-05
SoftwareSerial BTSerial(0, 1); // RX, TX

const int ledPin = 13; // LED connected to digital pin 13

void setup() {
  // Initialize the digital pin as an output
  pinMode(ledPin, OUTPUT);
  
  // Start the serial communication
  Serial.begin(9600);
  BTSerial.begin(9600);
}

void loop() {
  if (BTSerial.available()) {
    String command = BTSerial.readStringUntil('\n');
    
    // Remove any trailing spaces or newlines
    command.trim();
    
    if (command == "1" || command == "turn on") {
      digitalWrite(ledPin, HIGH); // Turn LED on
      Serial.println("LED turned on");
    } else if (command == "0" || command == "turn off") {
      digitalWrite(ledPin, LOW); // Turn LED off
      Serial.println("LED turned off");
    }
    
    // Print the received command for debugging purposes
    Serial.println("Received command: " + command);
  }
}
