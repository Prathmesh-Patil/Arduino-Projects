// Viral Science www.viralsciencecreativity.com www.youtube.com/c/viralscience
// Smart Attendance System with Google Sheets and LCD Display
#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <LiquidCrystal_I2C.h>

// Define pins
#define SS_PIN   D4
#define RST_PIN  D3
#define BUZZER   D8

// Initialize RFID and LCD
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Change LCD Address to 0x27 if 0x3F doesn't work

// Replace with your network credentials
const char* ssid = "Venkateshwara School";
const char* password = "Venkateshwara@7588";

// Replace with your Google Sheets Script ID
const String googleScriptID = "AKfycbzG2CSGkUAWZGc0vV-mbN3RLD8Vse0oX7Sh4V8zjtnBoXDTLjtLYlykErspriM0xE-CDg";

// Predefined Tag IDs (in HEX format) and associated names
String validTags[] = {"913C232F", "595E5318", "60371359", "D4F44564","54EC834","945A9164"}; // Replace with your tag IDs
String names[] = {"Aryan", "Harsh", "Viraj","Ruchali","Pradnya","Pruthviraj"}; // Replace with the names associated with your tags
const int numTags = sizeof(validTags) / sizeof(validTags[0]);

WiFiClient client; // Create a WiFiClient object

void setup() {
  Serial.begin(9600);
  SPI.begin();      // Init SPI bus
  rfid.PCD_Init();  // Init MFRC522

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Initializing");
  for (int i = 0; i < 5; i++) {
    lcd.setCursor(12 + i, 0);
    lcd.print(".");
    delay(500);
  }
  
  // Connect to Wi-Fi
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Set BUZZER as OUTPUT
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  // Display instruction on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scan your Card");

  // Look for new RFID cards
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }

  // Reading RFID tag
  String tagID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    tagID += String(rfid.uid.uidByte[i], HEX);
  }
  tagID.toUpperCase();
  tagID.replace(" ", ""); // Removing any spaces in the Tag ID string
  Serial.println("Scanned Tag ID: " + tagID);

  // Check if the scanned tag matches any valid tags
  bool isValid = false;
  String name = "";
  for (int i = 0; i < numTags; i++) {
    if (tagID.equals(validTags[i])) {
      isValid = true;
      name = names[i];
      break;
    }
  }

  // If valid, send the Tag ID to Google Sheets
  if (isValid) {
    if (WiFi.status() == WL_CONNECTED) {
      std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
      client->setInsecure(); // Ignore SSL certificate validation

      HTTPClient https;
      String url = "https://script.google.com/macros/s/" + googleScriptID + "/exec?name=" + name;
      https.begin(*client, url); // Updated begin() method
      int httpCode = https.GET();
      if (httpCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpCode);
        Serial.println("Data sent to Google Sheets");

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Hello, " + name);
        lcd.setCursor(0, 1);
        lcd.print("Data Recorded");
      } else {
        Serial.print("Error sending data to Google Sheets. HTTP Response code: ");
        Serial.println(httpCode);
      }
      https.end();
    }
  } else {
    Serial.println("Tag ID not recognized");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Unrecognized Tag");
  }

  // Sound the buzzer
  digitalWrite(BUZZER, HIGH);
  delay(200);
  digitalWrite(BUZZER, LOW);
  
  delay(1000);
  rfid.PICC_HaltA(); // Stop reading
}
