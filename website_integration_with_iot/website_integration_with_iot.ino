#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
 
const char *ssid = "PRATH";
const char *password = "987654321";
const int ledPin = 5;
 
bool ledState = false;
 
ESP8266WebServer server(80);
 
void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
 
  // Connect to WiFi
  connectToWiFi();
 
  // Route for root / web page
  server.on("/", HTTP_GET, handleRoot);
  // Route to toggle LED
  server.on("/toggle", HTTP_GET, handleToggleLED);
 
  // Start server
  server.begin();
}
 
void loop() {
  server.handleClient();
 
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wi-Fi disconnected. Turning off LED.");
    digitalWrite(ledPin, LOW);
    delay(1000);
    connectToWiFi();
  }
}
 
void connectToWiFi() {
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println("IP Address: " + WiFi.localIP().toString());
}
 
void handleRoot() {
  String buttonLabel = ledState ? "Turn LED Off" : "Turn LED On";
  String buttonLink = ledState ? "/toggle?state=off" : "/toggle?state=on";
  String html = "<h1>ESP8266 Web Server</h1>";
  html += "<p><a href=\"" + buttonLink + "\">" + buttonLabel + "</a></p>";
  server.send(200, "text/html", html);
}
 
void handleToggleLED() {
  if (server.arg("state") == "on") {
    digitalWrite(ledPin, HIGH);
    ledState = true;
  } else if (server.arg("state") == "off") {
    digitalWrite(ledPin, LOW);
    ledState = false;
  }
  server.sendHeader("Location", "/", true);
  server.send(303);
}