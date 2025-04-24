#include <ESP8266WiFi.h>
#define statusled 16
#define WiFi_SSID "PRATH"
#define WiFi_PASS "987654321"
void setup() {
  // put your setup code here, to run once:
  pinMode(statusled, OUTPUT);
  Serial.begin(9600);
  WiFi.begin(WiFi_SSID, WiFi_PASS);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(statusled, LOW);
  } else {
    digitalWrite(statusled, HIGH);
  }
}
