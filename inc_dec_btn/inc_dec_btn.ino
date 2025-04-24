// number counter machine 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD address to 0x27 for a 16 chars and 2 line display

const int increaseButton = 9;
const int decreaseButton = 10; // Define the pin for the decrease button

int buttonState;       
int lastButtonState = LOW;

int buttonState1;       
int lastButtonState1 = LOW;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 10;

int value = 0;

void setup() {
  lcd.init();                      // Initialize the LCD
  lcd.backlight();                 // Turn on the backlight
  lcd.begin(16, 2);                // Set the LCD dimensions (16 characters, 2 lines)
  pinMode(increaseButton, INPUT_PULLUP);
  pinMode(decreaseButton, INPUT_PULLUP); // Set decrease button pin as input with pull-up resistor
}

void loop() {-
  increaseParameter();
  decreaseParameter(); // Call the function to handle decrement button
  lcd.clear();                     // Clear the LCD display
  lcd.setCursor(0, 0);            // Set cursor to the first column of the first row
  lcd.print("Number Ticker: ");           // Print "Value: "
  lcd.print(value);               // Print the current value
  delay(200);                      // Delay for visibility
}

void increaseParameter() {
  int reading = digitalRead(increaseButton);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {

    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        value++;
      }
    }
  }
  lastButtonState = reading;
}

void decreaseParameter() {
  int reading1 = digitalRead(decreaseButton);

  if (reading1 != lastButtonState1) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {

    if (reading1 != buttonState1) {
      buttonState1 = reading1;

      if (buttonState1 == LOW) {
        value--; // Decrease the value when the button is pressed
      }
    }
  }
  lastButtonState1 = reading1;
}
