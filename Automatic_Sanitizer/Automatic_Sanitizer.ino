#define IRsensor 2
#define DCwater_pump 8

void setup() {
  pinMode(IRsensor, INPUT);
  pinMode(DCwater_pump, OUTPUT);  
  Serial.begin(9600);
}

int readPin = 0;

void loop() {
  readPin = digitalRead(IRsensor);
  
  if (readPin == LOW) { // If IR sensor detects something
    digitalWrite(DCwater_pump, HIGH); // Turn on pump
    Serial.println("DC Pump is ON Now!!");
    delay(150); // Run the pump for 100 milliseconds (adjust as needed)
    digitalWrite(DCwater_pump, LOW); // Turn off pump after short burst
  } else {
    Serial.println("No detection. Pump OFF.");
  }
  
  delay(500); // Small delay before checking sensor again
}
