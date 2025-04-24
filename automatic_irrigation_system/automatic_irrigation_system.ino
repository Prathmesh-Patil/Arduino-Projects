#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Initialize the LCD
LiquidCrystal_I2C dis(0x27, 16, 2);

// Initialize the servo motor
Servo myServo;

void setup() {
  Serial.begin(9600);
  
  // Initialize the LCD
  dis.init();
  dis.backlight();
  dis.clear();
  
  // Attach the servo to pin 2
  myServo.attach(9);

  // Initial setup display message
  dis.setCursor(0, 0);
  dis.print("IRRIGATION");
  dis.setCursor(0, 1);
  dis.print("SYSTEM IS ON ");
  for (int a = 12; a <= 15; a++) {
    dis.setCursor(a, 1);
    dis.print(".");
    delay(1500);
  }
  dis.clear();
}

void loop() {
  int value = analogRead(A0);
  Serial.println(value);

  // Control the servo based on moisture value
  if (value > 950) {
    myServo.write(180); // Rotate servo to 0 degrees (OFF position)
    dis.setCursor(0, 0);
    dis.print("SERVO IS AT 180  ");
  } else {
    myServo.write(0); // Rotate servo to 180 degrees (ON position)
    dis.setCursor(0, 0);
    dis.print("SERVO IS AT 0");
  }
  
  // Clear the second line before printing new data
  dis.setCursor(0, 1);
  dis.print("                "); // Clear the line with spaces
  
  // Display moisture levels
  if (value < 300) {
    dis.setCursor(0, 1);
    dis.print("MOISTURE : HIGH");
  } else if (value >= 300 && value <= 950) {
    dis.setCursor(0, 1);
    dis.print("MOISTURE : MID ");
  } else if (value > 950) {
    dis.setCursor(0, 1);
    dis.print("MOISTURE : LOW ");
  }

  delay(1000); // Add a delay to make the loop run every second
}
