#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);  // Initiate a serial communication
  SPI.begin();         // Initiate SPI bus
  mfrc522.PCD_Init();  // Initiate MFRC522
  lcd.init();          // Initialize LCD
  lcd.backlight();     // Turn on the backlight
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
    Serial.println("Yash");
    lcd.setCursor(0, 0);
    lcd.print("Yash");
    delay(2000);
  } else if (content.substring(1) == "59 5E 53 18")  // Change here the UID of the card/cards that you want to give access
  {
    Serial.println("Sachin");
    lcd.setCursor(0, 0);
    lcd.print("Sachin");
    delay(2000);
  } else if (content.substring(1) == "60 37 13 59")  // Change here the UID of the card/cards that you want to give access
  {
    Serial.println("Sanket");
    lcd.setCursor(0, 0);
    lcd.print("Sanket");
    delay(2000);
  } else {
    Serial.println("Access denied");
    lcd.setCursor(0, 0);
    lcd.print("Access denied");
    delay(3000);
  }
}
