#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "dht.h"

#define dht_apin A0  // Analog Pin sensor is connected to
#define fan_pin 8    // Pin for the fan control (relay or transistor)

dht DHT;

// Initialize the I2C LCD (address 0x27 or 0x3F depending on your I2C module)
LiquidCrystal_I2C lcd(0x27, 16, 2); // Change 0x27 to your specific I2C address if necessary

void setup() {
  Serial.begin(9600);
  delay(500); // Delay to let system boot
  Serial.println("DHT11 Humidity & Temperature Sensor\n\n");

  lcd.init();       // Initialize the LCD
  lcd.backlight();  // Turn on the backlight
  lcd.setCursor(0, 0);
  lcd.print("DHT11 Sensor");
  delay(2000);
  lcd.clear();

  pinMode(fan_pin, OUTPUT); // Set fan pin as an output
  digitalWrite(fan_pin, LOW); // Ensure fan is off at startup
}

void loop() {
  // Start of Program 
  DHT.read11(dht_apin);
  
  // Print values to Serial Monitor
  Serial.print("Current humidity = ");
  Serial.print(DHT.humidity);
  Serial.print("%  ");
  Serial.print("Temperature = ");
  Serial.print(DHT.temperature); 
  Serial.println("C  ");

  // Display values on I2C LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(DHT.temperature);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(DHT.humidity);
  lcd.print("%");

  // Control fan based on both temperature and humidity
  if (DHT.temperature > 27 || DHT.humidity < 66) {
    digitalWrite(fan_pin, HIGH); // Turn fan on
    Serial.println("Fan is ON (Temp > 29C or Humidity < 65%)");
  } else {
    digitalWrite(fan_pin, LOW); // Turn fan off
    Serial.println("Fan is OFF (Temp <= 29C and Humidity >= 65%)");
  }

  delay(5000); // Wait 5 seconds before accessing sensor again
}
