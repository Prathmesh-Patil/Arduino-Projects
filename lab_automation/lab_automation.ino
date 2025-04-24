// #include <IRremote.h>

// const byte IR_RECEIVE_PIN = 2;

// void setup()
// {
//    Serial.begin(115200);
//    Serial.println("IR Receive Test");
//    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
// }

// void loop()
// {
//    if (IrReceiver.decode())
//    {
//       // Print the IR command in decimal
//       Serial.print("Decimal: ");
//       Serial.println(IrReceiver.decodedIRData.command);

//       // Print the IR command in HEX
//       Serial.print("HEX: 0x");
//       Serial.println(IrReceiver.decodedIRData.command, HEX);

//       // Resume to receive the next code
//       IrReceiver.resume();
//    }
// }

#include <IRremote.h>

#define IR_RECEIVE_PIN 2  // IR sensor output pin
#define RELAY1 3          // Relay 1 connected to Pin 3
#define RELAY2 4          // Relay 2 connected to Pin 4
#define RELAY3 5          // Relay 3 connected to Pin 5
#define RELAY4 6          // Relay 4 connected to Pin 6

bool relay1State = LOW;
bool relay2State = LOW;
bool relay3State = LOW;
bool relay4State = LOW;

void setup() {
    Serial.begin(9600);
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
    
    pinMode(RELAY1, OUTPUT);
    pinMode(RELAY2, OUTPUT);
    pinMode(RELAY3, OUTPUT);
    pinMode(RELAY4, OUTPUT);

    // Initially turn off all relays (set to LOW)
    digitalWrite(RELAY1, HIGH); 
    digitalWrite(RELAY2, HIGH);
    digitalWrite(RELAY3, HIGH);
    digitalWrite(RELAY4, HIGH);
}

void loop() {
    // Check for IR remote signals
    if (IrReceiver.decode()) {
        unsigned long value = IrReceiver.decodedIRData.command;
        Serial.print("Received HEX: 0x");
        Serial.println(value, HEX);

        switch (value) {
            case 0xA: // If button '2' is pressed
                relay1State = !relay1State; // Toggle the state of Relay 2
                digitalWrite(RELAY1, relay1State); // Apply the new state
                break;
            case 0x1B: // If button '2' is pressed
                relay2State = !relay2State; // Toggle the state of Relay 2
                digitalWrite(RELAY2, relay2State); // Apply the new state
                break;
            case 0xC: // If button '3' is pressed
                relay3State = !relay3State; // Toggle the state of Relay 3
                digitalWrite(RELAY3, relay3State); // Apply the new state
                break;
            case 0x1F: // If button '4' is pressed
                relay4State = !relay4State; // Toggle the state of Relay 4
                digitalWrite(RELAY4, relay4State); // Apply the new state
                break;
            default:
                // If any other button is pressed, do nothing
                break;
        }

        IrReceiver.resume(); // Receive the next IR signal
    }
}



