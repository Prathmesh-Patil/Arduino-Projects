#include <LiquidCrystal_I2C.h>
#include<Wire.h>
#include <ESP8266WiFi.h>

// Enter your WiFi SSID and password here
const char* ssid = "PRATH";
const char* password = "987654321";

LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust the address if needed

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);

  // Initialize the LCD
  lcd.init();

  // Turn on the backlight
  lcd.backlight();

  // Print to the LCD
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");

  // Connect to WiFi
  connectToWiFi();
}

void loop() {
  // Your loop code here
}

void connectToWiFi() {
  // Attempt to connect to WiFi network
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Print message to LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connected");
  lcd.setCursor(0, 1);
  lcd.print("IP: ");
  lcd.print(WiFi.localIP());
}
