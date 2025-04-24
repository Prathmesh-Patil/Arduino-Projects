int sensor = 2;           // Connected to digital output of KY-038 sound sensor module
int ledPins[5] = {4, 5, 6, 7, 8}; // Array of LED pins (connected to digital pins 4, 5, 6, 7, and 8)
int clap_threshold = 500;  // Time in milliseconds to filter out noise
unsigned long last_clap_time = 0; // To track the time of the last clap

boolean are_leds_on = false; // To track the state of the LEDs

void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT); // Setting the pin to input for reading data

  // Initialize all LED pins as outputs and turn them off initially
  for (int i = 0; i < 5; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
}

void loop() {
  int data = digitalRead(sensor); // Reading data from the sensor
  unsigned long current_time = millis(); // Get the current time

  // Detects a clap and checks if enough time has passed since the last clap
  if (data == 1 && (current_time - last_clap_time > clap_threshold)) {
    are_leds_on = !are_leds_on; // Toggle the LED state

    // Turn all LEDs on or off based on the toggle state
    for (int i = 0; i < 5; i++) {
      digitalWrite(ledPins[i], are_leds_on ? HIGH : LOW);
    }

    Serial.print("LEDs are now ");
    Serial.println(are_leds_on ? "ON" : "OFF");

    last_clap_time = current_time; // Update the last clap time
  }
}
