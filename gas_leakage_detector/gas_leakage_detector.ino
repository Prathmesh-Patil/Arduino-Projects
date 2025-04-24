#include <Servo.h>

const int gas_pin = A0;  // Use an analog pin for gas sensor
const int buzzer = 13;
const int gasThreshold = 450;

Servo gasServo;

void setup() {
  Serial.begin(9600);
  pinMode(gas_pin,INPUT);
  pinMode(buzzer, OUTPUT);
  gasServo.attach(10);
  gasServo.write(10);
}

void loop() {
  int gasValue = analogRead(gas_pin);
  Serial.print("Gas value is: ");
  Serial.println(gasValue);

  if (gasValue > gasThreshold) {
    gasServo.write(160);
    Serial.println("Gas detected!");
    digitalWrite(buzzer, HIGH);
  } else {
    gasServo.write(10);  // Reset servo position when gas is not detected
    Serial.println("Gas not detected.");
    digitalWrite(buzzer, LOW);
  }

  delay(2000);
}
