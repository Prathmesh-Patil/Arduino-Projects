// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>

// #define DOT_LENGTH 250
// #define DASH_LENGTH (DOT_LENGTH * 3)
// #define SPACE_LENGTH (DOT_LENGTH * 3)

// LiquidCrystal_I2C lcd(0x27, 16, 2); // Initialize the LCD with I2C address 0x27, 16 columns, and 2 rows

// const int dotButtonPin = 2; // Pin for the dot button
// const int dashButtonPin = 3; // Pin for the dash button
// const int enterButtonPin = 4; // Pin for the enter button

// bool dotButtonState = HIGH; // current state of the dot button
// bool dashButtonState = HIGH; // current state of the dash button
// bool enterButtonState = HIGH; // current state of the enter button

// bool dotButtonPressed = false; // flag to indicate dot button pressed
// bool dashButtonPressed = false; // flag to indicate dash button pressed
// bool enterButtonPressed = false; // flag to indicate enter button pressed

// String currentInput = ""; // String to store the current Morse code input

// // Morse code dictionary
// const char* morseCode[] = {
//   ".-",   // A
//   "-...", // B
//   "-.-.", // C
//   "-..",  // D
//   ".",    // E
//   "..-.", // F
//   "--.",  // G
//   "....", // H
//   "..",   // I
//   ".---", // J
//   "-.-",  // K
//   ".-..", // L
//   "--",   // M
//   "-.",   // N
//   "---",  // O
//   ".--.", // P
//   "--.-", // Q
//   ".-.",  // R
//   "...",  // S
//   "-",    // T
//   "..-",  // U
//   "...-", // V
//   ".--",  // W
//   "-..-", // X
//   "-.--", // Y
//   "--.."  // Z
// };

// void setup() {
//   lcd.init();                      // Initialize the LCD
//   lcd.backlight();                 // Turn on the backlight

//   pinMode(dotButtonPin, INPUT); // Set dot button pin as input
//   pinMode(dashButtonPin, INPUT); // Set dash button pin as input
//   pinMode(enterButtonPin, INPUT); // Set enter button pin as input
// }

// void loop() {
//   // Check for dot button press
//   if (digitalRead(dotButtonPin) == LOW && dotButtonState == HIGH) {
//     dotButtonPressed = true;
//   }
//   dotButtonState = digitalRead(dotButtonPin);

//   // Check for dash button press
//   if (digitalRead(dashButtonPin) == LOW && dashButtonState == HIGH) {
//     dashButtonPressed = true;
//   }
//   dashButtonState = digitalRead(dashButtonPin);

//   // Check for enter button press
//   if (digitalRead(enterButtonPin) == LOW && enterButtonState == HIGH) {
//     enterButtonPressed = true;
//   }
//   enterButtonState = digitalRead(enterButtonPin);

//   // Process button presses
//   if (dotButtonPressed) {
//     currentInput += ".";
//     lcd.clear();
//     lcd.print("Input: " + currentInput);
//     delay(DOT_LENGTH);
//     dotButtonPressed = false;
//   }
//   if (dashButtonPressed) {
//     currentInput += "-";
//     lcd.clear();
//     lcd.print("Input: " + currentInput);
//     delay(DASH_LENGTH);
//     dashButtonPressed = false;
//   }
//   if (enterButtonPressed) {
//     decodeAndDisplay(); // Decode and display the input
//     currentInput = ""; // Reset the input
//     lcd.clear();
//     lcd.print("Input: ");
//     delay(SPACE_LENGTH * 2);
//     enterButtonPressed = false;
//   }
// }

// // Function to decode and display Morse code input
// void decodeAndDisplay() {
//   for (int i = 0; i < 26; i++) {
//     if (strcmp(currentInput.c_str(), morseCode[i]) == 0) {
//       char character = 'A' + i;
//       lcd.clear();
//       lcd.print("Character: ");
//       lcd.print(character);
//       delay(SPACE_LENGTH * 2); // Delay to display the character
//       return;
//     }
//   }
//   // If no matching Morse code found, display error
//   lcd.clear();
//   lcd.print("Error: Invalid Morse code");
//   delay(SPACE_LENGTH * 2); // Delay to display the error
// }

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DOT_LENGTH 250
#define DASH_LENGTH (DOT_LENGTH * 3)
#define SPACE_LENGTH (DOT_LENGTH * 3)
#define CHAR_SPACE_LENGTH (DOT_LENGTH * 5) // Extra space between characters

LiquidCrystal_I2C lcd(0x27, 16, 2); // Initialize the LCD with I2C address 0x27, 16 columns, and 2 rows

const int dotButtonPin = 2; // Pin for the dot button
const int dashButtonPin = 3; // Pin for the dash button
const int enterButtonPin = 4; // Pin for the enter button

bool dotButtonState = HIGH; // current state of the dot button
bool dashButtonState = HIGH; // current state of the dash button
bool enterButtonState = HIGH; // current state of the enter button

bool dotButtonPressed = false; // flag to indicate dot button pressed
bool dashButtonPressed = false; // flag to indicate dash button pressed
bool enterButtonPressed = false; // flag to indicate enter button pressed

String currentInput = ""; // String to store the current Morse code input

// Morse code dictionary
const char* morseCode[] = {
  ".-",   // A
  "-...", // B
  "-.-.", // C
  "-..",  // D
  ".",    // E
  "..-.", // F
  "--.",  // G
  "....", // H
  "..",   // I
  ".---", // J
  "-.-",  // K
  ".-..", // L
  "--",   // M
  "-.",   // N
  "---",  // O
  ".--.", // P
  "--.-", // Q
  ".-.",  // R
  "...",  // S
  "-",    // T
  "..-",  // U
  "...-", // V
  ".--",  // W
  "-..-", // X
  "-.--", // Y
  "--.."  // Z
};

void setup() {
  lcd.init();                      // Initialize the LCD
  lcd.backlight();                 // Turn on the backlight

  pinMode(dotButtonPin, INPUT); // Set dot button pin as input
  pinMode(dashButtonPin, INPUT); // Set dash button pin as input
  pinMode(enterButtonPin, INPUT); // Set enter button pin as input
}

void loop() {
  // Check for dot button press
  if (digitalRead(dotButtonPin) == LOW && dotButtonState == HIGH) {
    dotButtonPressed = true;
  }
  dotButtonState = digitalRead(dotButtonPin);

  // Check for dash button press
  if (digitalRead(dashButtonPin) == LOW && dashButtonState == HIGH) {
    dashButtonPressed = true;
  }
  dashButtonState = digitalRead(dashButtonPin);

  // Check for enter button press
  if (digitalRead(enterButtonPin) == LOW && enterButtonState == HIGH) {
    enterButtonPressed = true;
  }
  enterButtonState = digitalRead(enterButtonPin);

  // Process button presses
  if (dotButtonPressed) {
    currentInput += ".";
    lcd.clear();
    lcd.print("Input: " + currentInput);
    delay(DOT_LENGTH);
    dotButtonPressed = false;
  }
  if (dashButtonPressed) {
    currentInput += "-";
    lcd.clear();
    lcd.print("Input: " + currentInput);
    delay(DASH_LENGTH);
    dashButtonPressed = false;
  }
  if (enterButtonPressed) {
    printName(); // Print the name using Morse code
    currentInput = ""; // Reset the input
    lcd.clear();
    lcd.print("Input: ");
    delay(SPACE_LENGTH * 2);
    enterButtonPressed = false;
  }
}

// Function to print name "JOHN" using Morse code
void printName() {
  const char* nameMorse[] = {".---", "---", "....", "-."}; // Morse code representation of "JOHN"

  lcd.clear();
  lcd.print("Name: ");
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < strlen(nameMorse[i]); j++) {
      if (nameMorse[i][j] == '.') {
        lcd.print(".");
        delay(DOT_LENGTH);
      } else if (nameMorse[i][j] == '-') {
        lcd.print("-");
        delay(DASH_LENGTH);
      }
      lcd.clear();
      lcd.print("Name: ");
      delay(SPACE_LENGTH);
    }
    delay(CHAR_SPACE_LENGTH);
  }
}
