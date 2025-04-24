#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Store previous card statuses
bool yashIn = false;
bool sachinIn = false;
bool sanketIn = false;
bool sohamIn = false;
bool prajwalIn = false;

void setup() {
  Serial.begin(9600);  // Initiate a serial communication
  SPI.begin();         // Initiate SPI bus
  mfrc522.PCD_Init();  // Initiate MFRC522
  lcd.init();          // Initialize LCD
  lcd.backlight();     // Turn on the backlight

  // Display initial message
  lcd.setCursor(0, 0);
  lcd.print("Attendance");
  lcd.setCursor(0, 1);
  lcd.print("System");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Student ID");
}

void loop() {
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Show UID on serial monitor
  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  content.toUpperCase();
  lcd.clear();  // Clear the LCD before displaying new content

  // Check UID and display corresponding message on the LCD
  if (content.substring(1) == "91 3C 23 2F")  // Change here the UID of the card/cards that you want to give access
  {
    if (yashIn) {
      Serial.println("Yash OUT");
      lcd.setCursor(0, 0);
      lcd.print("Yash OUT");
      yashIn = false;
    } else {
      Serial.println("Yash IN");
      lcd.setCursor(0, 0);
      lcd.print("Yash IN");
      yashIn = true;
    }
    delay(2000);
  } else if (content.substring(1) == "59 5E 53 18")  // Change here the UID of the card/cards that you want to give access
  {
    if (sachinIn) {
      Serial.println("Sachin OUT");
      lcd.setCursor(0, 0);
      lcd.print("Sachin OUT");
      sachinIn = false;
    } else {
      Serial.println("Sachin IN");
      lcd.setCursor(0, 0);
      lcd.print("Sachin IN");
      sachinIn = true;
    }
    delay(2000);
  } else if (content.substring(1) == "60 37 13 59")  // Change here the UID of the card/cards that you want to give access
  {
    if (sanketIn) {
      Serial.println("Sanket OUT");
      lcd.setCursor(0, 0);
      lcd.print("Sanket OUT");
      sanketIn = false;
    } else {
      Serial.println("Sanket IN");
      lcd.setCursor(0, 0);
      lcd.print("Sanket IN");
      sanketIn = true;
    }
    delay(2000);
  } else if (content.substring(1) == "D4 F4 45 64")  // UID for Soham
  {
    if (sohamIn) {
      Serial.println("Soham OUT");
      lcd.setCursor(0, 0);
      lcd.print("Soham OUT");
      sohamIn = false;
    } else {
      Serial.println("Soham IN");
      lcd.setCursor(0, 0);
      lcd.print("Soham IN");
      sohamIn = true;
    }
    delay(2000);
  } else if (content.substring(1) == "94 5A 91 64")  // UID for Yash
  {
    if (yashIn) {
      Serial.println("Yash OUT");
      lcd.setCursor(0, 0);
      lcd.print("Yash OUT");
      yashIn = false;
    } else {
      Serial.println("Yash IN");
      lcd.setCursor(0, 0);
      lcd.print("Yash IN");
      yashIn = true;
    }
    delay(2000);
  } else if (content.substring(1) == "54 0E C8 34")  // UID for Prajwal
  {
    if (prajwalIn) {
      Serial.println("Prajwal OUT");
      lcd.setCursor(0, 0);
      lcd.print("Prajwal OUT");
      prajwalIn = false;
    } else {
      Serial.println("Prajwal IN");
      lcd.setCursor(0, 0);
      lcd.print("Prajwal IN");
      prajwalIn = true;
    }
    delay(2000);
  } else {
    Serial.println("Access denied");
    lcd.setCursor(0, 0);
    lcd.print("Access denied");
    delay(3000);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Student ID");
}
