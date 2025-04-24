#define BLYNK_TEMPLATE_ID "TMPL3tQ8q3E-8"
#define BLYNK_TEMPLATE_NAME "Smart irrigation"
#define BLYNK_AUTH_TOKEN "bC9xNMs5uZKVZWweHnBePJg6DHMdWES4"
#define BLYNK_PRINT Serial

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Venkateshwara School";
char pass[] = "Venkateshwara@7588";

SimpleTimer timer;
const int relayPin = D5;  // Relay signal pin connected to D5

void checkWiFi();  // Function to check Wi-Fi status

void setup()
{
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);  // Set the relay pin as output
  digitalWrite(relayPin, LOW);  // Set relay to OFF initially (HIGH means off for active LOW relay)

  timer.setInterval(1000L, sendMoisture);  // Moisture reading function every second
  timer.setInterval(5000L, checkWiFi);  // Wi-Fi check every 5 seconds

  Blynk.begin(auth, ssid, pass);
}

int sensor = 0;
int output = 0;

void sendMoisture()
{
  sensor = analogRead(A0);  // Read analog value from moisture sensor

  // Adjust the mapping based on calibration of the sensor
  output = map(sensor, 1023, 300, 0, 100);  // Map sensor value (dry to wet) to a percentage
  output = constrain(output, 0, 100);  // Ensure output is within 0-100%

  Serial.print("Moisture = ");
  Serial.print(output);
  Serial.println("%");

  Blynk.virtualWrite(V2, output);  // Send moisture data to Blynk on virtual pin V2
}

void checkWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wi-Fi Disconnected!");
  } else {
    Serial.println("Wi-Fi Connected!");
  }
}

// Blynk function to control relay via virtual pin V1
BLYNK_WRITE(V1)
{
  int relayState = param.asInt();  // Get value from Blynk app (0 or 1)
  
  if (relayState == 1) {
    digitalWrite(relayPin, HIGH);  // Turn ON the relay (active LOW)
    Serial.println("Blynk V1 - Relay ON (Pump ON) - Acknowledged");
  } else {
    digitalWrite(relayPin, LOW);  // Turn OFF the relay (active LOW)
    Serial.println("Blynk V1 - Relay OFF (Pump OFF) - Acknowledged");
  }
}

void loop()
{
  Blynk.run();
  timer.run();
}
