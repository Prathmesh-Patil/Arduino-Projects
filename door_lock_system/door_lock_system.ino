#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Password.h>

#define buzzer 11

Servo servo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

Password password = Password("4444"); // Set your password here

byte maxPasswordLength = 4; // Set the length of the password
byte currentPasswordLength = 0;
byte a = 5; // Cursor position for displaying * on the LCD
bool doorState = false; // false means locked, true means open

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns

char keys[ROWS][COLS] = {
  {'D', 'C', 'B', 'A'},
  {'#', '9', '6', '3'},
  {'0', '8', '5', '2'},
  {'*', '7', '4', '1'}
};

byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  servo.attach(10);
  servo.write(70); // Initial position for locked door
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("WELCOME TO");
  lcd.setCursor(0, 1);
  lcd.print("DOOR LOCK SYSTEM");
  delay(3000);
  lcd.clear();
}

void loop() {
  lcd.setCursor(1, 0);
  lcd.print("ENTER PASSWORD");

  char key = keypad.getKey();
  if (key != NO_KEY) {
    delay(60);
    if (key == 'C') {
      resetPassword();
    } else if (key == 'D') {
      checkPassword();
    } else {
      processNumberKey(key);
    }
  }
}

void processNumberKey(char key) {
  if (currentPasswordLength < maxPasswordLength) {
    lcd.setCursor(a, 1);
    lcd.print("*");
    a++;
    if (a == 11) {
      a = 5;
    }
    currentPasswordLength++;
    password.append(key);
  }
}

void checkPassword() {
  if (password.evaluate()) {
    doorState = !doorState; // Toggle the door state
    if (doorState) {
      openDoor();
    } else {
      lockDoor();
    }
  } else {
    wrongPassword();
  }
  resetPassword();
}

void openDoor() {
  digitalWrite(buzzer, HIGH);
  delay(300);
  digitalWrite(buzzer, LOW);
  servo.write(160); // Open position
  lcd.setCursor(0, 0);
  lcd.print("CORRECT PASSWORD");
  lcd.setCursor(0, 1);
  lcd.print("DOOR OPENED");
  delay(2000);
  lcd.clear();
}

void lockDoor() {
  digitalWrite(buzzer, HIGH);
  delay(300);
  digitalWrite(buzzer, LOW);
  servo.write(70); // Locked position
  lcd.setCursor(0, 0);
  lcd.print("CORRECT PASSWORD");
  lcd.setCursor(2, 1);
  lcd.print("DOOR LOCKED");
  delay(2000);
  lcd.clear();
}

void wrongPassword() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    delay(200);
  }
  lcd.setCursor(0, 0);
  lcd.print("WRONG PASSWORD!");
  lcd.setCursor(0, 1);
  lcd.print("PLEASE TRY AGAIN");
  delay(2000);
  lcd.clear();
}

void resetPassword() {
  password.reset();
  currentPasswordLength = 0;
  lcd.clear();
  a = 5;
}
