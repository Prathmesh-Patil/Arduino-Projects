int sensor = 2; // Connected to digital output of KY-038 sound sensor module
int ledPins[] = {3, 4, 5, 6, 7, 8, 9}; // Array to store the pin numbers of the 7 LEDs
int numLeds = 7; // Number of LEDs
int clap_threshold = 500; // Time in milliseconds to filter out noise
unsigned long last_clap_time = 0; // To track the time of the last clap

boolean leds_on = false; // To track the state of the LEDs (initially off)

void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT); // Setting the pin to input for reading data
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT); // Setting each LED pin to output
    digitalWrite(ledPins[i], LOW); // Ensure all LEDs are off initially
  }
}

void loop() {
  int data = digitalRead(sensor); // Reading data from the sensor
  unsigned long current_time = millis(); // Get the current time

  // Check if a signal is detected and if enough time has passed since the last signal
  if (data == 1 && (current_time - last_clap_time > clap_threshold)) {
    leds_on = !leds_on; // Toggle the LEDs state

    // Turn all LEDs on or off based on the new state
    for (int i = 0; i < numLeds; i++) {
      digitalWrite(ledPins[i], leds_on ? HIGH : LOW);
    }

    last_clap_time = current_time; // Update the last clap time
  }
}
