#include <Servo.h>
 
Servo myServo; // Create servo object to control a servo
 
// Assign the pins connected to the LDRs
const int ldrLeftPin = A0; // LDR on the left
const int ldrRightPin = A1; // LDR on the right
 
// Variables to store the LDR values
int ldrLeftValue = 0;
int ldrRightValue = 0;
 
void setup() {
  myServo.attach(9); // Attaches the servo on pin 9 to the servo object
  Serial.begin(9600); // Starts the serial communication
}
 
void loop() {
  ldrLeftValue = analogRead(ldrLeftPin); // Reads the value from the left LDR
  ldrRightValue = analogRead(ldrRightPin); // Reads the value from the right LDR
 
  Serial.print("Left LDR: ");
  Serial.print(ldrLeftValue);
  Serial.print("\tRight LDR: ");
  Serial.println(ldrRightValue);
 
  // Invert the servo movement based on the light detected
  if (ldrLeftValue > ldrRightValue) {
    myServo.write(0); // Rotate servo to the right if more light on the left
  } else if (ldrRightValue > ldrLeftValue) {
    myServo.write(180); // Rotate servo to the left if more light on the right
  } else {
    myServo.write(90); // Keep servo in the middle if both values are equal
  }
 
  delay(500); // Wait for half a second
}
