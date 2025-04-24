#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "Venkateshwara School"
#define WIFI_PASSWORD "Venkateshwara@7588"

// Insert Firebase project API Key
#define API_KEY "AIzaSyBYXire_19EalTn0B2ndlm0LPoPzd8i690"

// Insert RTDB URL
#define DATABASE_URL "home-automation-fbfb4-default-rtdb.firebaseio.com/"

// Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

// Some important variables
String sValue, sValue2;
bool signupOK = false;

void setup() {
  Serial.begin(9600);
  pinMode(D1, OUTPUT);
  pinMode(D0, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key */
  config.api_key = API_KEY;

  /* Assign the RTDB URL */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Firebase sign up successful");
    signupOK = true;
  } else {
    Serial.print("Firebase sign up failed. Reason: ");
    Serial.println(config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  Serial.println("Inside loop"); // Debug statement

  if (Firebase.ready() && signupOK ) {
    Serial.println("Firebase ready"); // Debug statement

    if (Firebase.RTDB.getString(&fbdo, "/L1")) {
      Serial.println("Got data from /L1"); // Debug statement

      if (fbdo.dataType() == "string") {
        Serial.println("Data type is string"); // Debug statement

        sValue = fbdo.stringData();
        int a = sValue.toInt();
        Serial.print("Value of /L1: "); // Debug statement
        Serial.println(a); // Debug statement

        if (a == 1){
          digitalWrite(D1,HIGH);
        } else {
          digitalWrite(D1,LOW);
        }
      }
    }
    else {
      Serial.println("Failed to get data from /L1"); // Debug statement
      Serial.println(fbdo.errorReason()); // Debug statement
    }

    if (Firebase.RTDB.getString(&fbdo, "/L2")) {
      Serial.println("Got data from /L2"); // Debug statement

      if (fbdo.dataType() == "string") {
        Serial.println("Data type is string"); // Debug statement

        sValue2 = fbdo.stringData();
        int b = sValue2.toInt();
        Serial.print("Value of /L2: "); // Debug statement
        Serial.println(b); // Debug statement

        if (b == 1){
          digitalWrite(D0,HIGH);
        } else {
          digitalWrite(D0,LOW);
        }
      }
    }
    else {
      Serial.println("Failed to get data from /L2"); // Debug statement
      Serial.println(fbdo.errorReason()); // Debug statement
    }
  } else {
    Serial.println("Firebase not ready or sign up failed"); // Debug statement
  }

  delay(1000); // Add a delay to avoid flooding the serial monitor
}
