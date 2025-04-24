// Pin configuration
const int blinkSensorPin = 2;  // IR eyeblink sensor input pin
const int relayPin = 8;        // Relay control pin

// Variables
unsigned long blinkStartTime = 0;
const unsigned long blinkThreshold = 5000; // 5 seconds in milliseconds
bool isBlinkDetected = false;

void setup() {
  // Set relay pin as output
  pinMode(relayPin, OUTPUT);

  // Set sensor pin as input
  pinMode(blinkSensorPin, INPUT);

  // Initialize Serial Monitor for debugging
  Serial.begin(9600);
  Serial.println("Anti-Sleep Alarm System Initialized");
}

void loop() {
  // Read the sensor input
  int sensorValue = digitalRead(blinkSensorPin);

  // Check if the signal is low (eyes open)
  if (sensorValue == LOW) {
    // Run the motor when eyes are open
    digitalWrite(relayPin, HIGH);  // Turn on relay
    Serial.println("Eyes open: Motor ON");

    // Reset detection variables
    isBlinkDetected = false;
  }

  // Check if the signal is high (eyes closed)
  else if (sensorValue == HIGH) {
    if (!isBlinkDetected) {
      // Start the timer when blink is first detected
      isBlinkDetected = true;
      blinkStartTime = millis();
      Serial.println("Eyes closed: Starting timer...");
    }

    // Check if the signal stays high for 5 seconds
    if (isBlinkDetected && (millis() - blinkStartTime >= blinkThreshold)) {
      // Turn off the relay to stop the motor
      digitalWrite(relayPin, LOW);
      Serial.println("Eyes closed for 5 seconds: Motor OFF");
      
      // Reset detection variables
      isBlinkDetected = false;
    }
  }

  // Small delay to prevent flooding the Serial Monitor
  delay(100);
}
