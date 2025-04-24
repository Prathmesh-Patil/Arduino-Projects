#define BLYNK_TEMPLATE_ID "TMPL3aqIr-qhg" // Correct Template ID
#define BLYNK_TEMPLATE_NAME "Home Automation" // Correct Template Name
#define BLYNK_AUTH_TOKEN "IkwcnvwzyLaPaTKF-32RJGKS6e0uc9w3" // Your Blynk Auth Token

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define relay1 D0

char auth[] = BLYNK_AUTH_TOKEN; // Blynk auth token
char ssid[] = "PRATH"; // Your WiFi SSID
char pass[] = "987654321"; // Your WiFi password

BLYNK_WRITE(V0) {
  bool value1 = param.asInt();
  if (value1 == 1) {
    digitalWrite(relay1, LOW); // Turn relay ON
  } else {
    digitalWrite(relay1, HIGH); // Turn relay OFF
  }
}

void setup() {
  pinMode(relay1, OUTPUT);
  digitalWrite(relay1, HIGH); // Start with relay OFF
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

void loop() {
  Blynk.run();
}
