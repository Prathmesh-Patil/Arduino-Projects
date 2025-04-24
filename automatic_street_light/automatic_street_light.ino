const int LDRPin = A0;     // LDR connected to analog pin A0
const int threshold = 500; // Set a threshold value for LDR reading
const int ledPins[3] = {3, 4, 5}; // Array of LED pins connected to digital pins 3, 4, and 5

void setup() {
  Serial.begin(9600); // Initialize serial communication for debugging

  // Set up LED pins as outputs
  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW); // Turn off LEDs initially
  }
}

void loop() {
  int LDRValue = analogRead(LDRPin); // Read the LDR value
  Serial.println(LDRValue); // Print the LDR value for debugging

  if (LDRValue < threshold) { // If the LDR value is below the threshold (it's dark)
    for (int i = 0; i < 3; i++) {
      digitalWrite(ledPins[i], LOW); // Turn all LEDs on
    }
  } else { // If it's bright
    for (int i = 0; i < 3; i++) {
      digitalWrite(ledPins[i], HIGH); // Turn all LEDs off
    }
  }

  delay(1000); // Delay for 1 second before reading again
}
