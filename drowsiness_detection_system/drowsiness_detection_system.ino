const int eyeBlinkSensor = 2;
const int buzzer = 12;
const int led = 13;

void setup() {
  pinMode(eyeBlinkSensor, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = digitalRead(eyeBlinkSensor);
  
  if (sensorValue == LOW) { // Assuming LOW means eyes are closed
    digitalWrite(buzzer, HIGH);
    digitalWrite(led, HIGH);
    Serial.println("Drowsiness detected!");
    delay(1000); // Alert duration
  } else {
    digitalWrite(buzzer, LOW);
    digitalWrite(led, LOW);
  }
}
