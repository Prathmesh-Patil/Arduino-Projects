int flameInPin = 2;  // define pin 2 for flame sensor
int relayPin = 8;    // pin connected to relay

int onTime = 200;   // time in melliseond ON and wait before make another reading.
int offTime = 200;  // time in melliseond OFF and wait before make another reading.

void setup() {
  Serial.begin(9600);
  //Robojax Step By Step Arduino Course http://robojax.com/L/?id=338
  // out pins
  pinMode(flameInPin, INPUT);  // define flameInPin as input
  pinMode(relayPin, OUTPUT);   // define relayPin as output  for relay

  Serial.println("Flame Sensor");
}

void loop() {

  // read the flame sensor.
  if (digitalRead(flameInPin) == HIGH) {
    Serial.println("fire! fire! ");
    digitalWrite(relayPin, HIGH);  // Turn the relay ON
    delay(onTime);                 // keep the relay or switch ON for the onTime
  } else {
    digitalWrite(relayPin, LOW);  // Turn the relay OFF
    Serial.println("peace");
    delay(offTime);  // wait offTime  before reading again
  }
  
} 