#define FLOAT_SWITCH_PIN 2 // Connect float switch to digital pin 2

void setup() {
  Serial.begin(9600);       // Start the Serial Monitor
  pinMode(FLOAT_SWITCH_PIN, INPUT); // Set float switch pin as input
}

void loop() {
  int waterLevel = digitalRead(FLOAT_SWITCH_PIN); // Read float switch state

  if (waterLevel == LOW) {
    Serial.println("Water Level: LOW"); // Float is down
  } else {
    Serial.println("Water Level: OKAY"); // Float is up
  }

  delay(500); // Small delay to avoid flooding the Serial Monitor
}
