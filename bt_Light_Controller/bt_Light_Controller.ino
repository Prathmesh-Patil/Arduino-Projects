#include <SoftwareSerial.h>

#define RELAY_PIN 13  // Digital pin connected to relay module
#define RX_PIN 0   // Digital pin connected to Bluetooth module's TX pin
#define TX_PIN 1   // Digital pin connected to Bluetooth module's RX pin

SoftwareSerial bluetooth(RX_PIN, TX_PIN);  // RX, TX

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop() {
  if (bluetooth.available()) {
    char command = bluetooth.read();
    if (command == '1') {
      digitalWrite(RELAY_PIN, HIGH);  // Turn on the relay
      Serial.println("Bulb turned ON");
    } else if (command == '0') {
      digitalWrite(RELAY_PIN, LOW);   // Turn off the relay
      Serial.println("Bulb turned OFF");
    }
  }
}
