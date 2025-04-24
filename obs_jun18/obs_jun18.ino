// // // Define pins for motor control
// // const int a1 = 4; // A1 on motor driver module
// // const int a2 = 5; // A2 on motor driver module
// // const int b1 = 6; // B1 on motor driver module
// // const int b2 = 7; // B2 on motor driver module

// // // Define pin for IR sensor
// // const int irSensor = 8;

// // void setup() {
// //   // Set motor control pins as output
// //   pinMode(a1, OUTPUT);
// //   pinMode(a2, OUTPUT);
// //   pinMode(b1, OUTPUT);
// //   pinMode(b2, OUTPUT);

// //   // Set IR sensor pin as input
// //   pinMode(irSensor, INPUT);

// //   // Initialize motors to stop
// //   stopMotors();
// // }

// // void loop() {
// //   // Check if obstacle is detected
// //   if (digitalRead(irSensor) == HIGH) { // assuming LOW means obstacle detected
// //     stopMotors();
// //   } else {
// //     moveForward();
// //   }

// //   delay(100);  // Small delay to debounce sensor input
// // }

// // void moveForward() {
// //   digitalWrite(a1, HIGH);
// //   digitalWrite(a2, LOW);
// //   digitalWrite(b1, HIGH);
// //   digitalWrite(b2, LOW);
// // }

// // void stopMotors() {
// //   digitalWrite(a1, LOW);
// //   digitalWrite(a2, LOW);
// //   digitalWrite(b1, LOW);
// //   digitalWrite(b2, LOW);
// // }



// const int irSensor = 8;  // Pin connected to the IR sensor OUT
// const int a1 = 4;        // A1 on motor driver module
// const int a2 = 5;        // A2 on motor driver module
// const int b1 = 6;        // B1 on motor driver module
// const int b2 = 7;
// void setup() {
//   // Initialize the serial communication
//   Serial.begin(9600);
//   pinMode(a1, OUTPUT);
//   pinMode(a2, OUTPUT);
//   pinMode(b1, OUTPUT);
//   pinMode(b2, OUTPUT);

//   // Set the IR sensor pin as input
//   pinMode(irSensor, INPUT);
// }

// void loop() {
//   // Read the IR sensor value
//   int sensorValue = digitalRead(irSensor);

//   // Check if the sensor value indicates an obstacle
//   if (sensorValue == LOW) {  // Assuming LOW means obstacle detected
//     Serial.println("Object detected!");
//     motorStop();
//   } else {
//     Serial.println("No object detected.");
//   }

//   // Small delay to avoid spamming the serial monitor
//   delay(500);
// }
// void motorStop() {
//   digitalWrite(a1, LOW);
//   digitalWrite(a2, LOW);
//   digitalWrite(b1, LOW);
//   digitalWrite(b2, LOW);
// }

// Define pins for motor control
const int a1 = 4; // A1 on motor driver module
const int a2 = 5; // A2 on motor driver module
const int b1 = 6; // B1 on motor driver module
const int b2 = 7; // B2 on motor driver module

// Define pin for IR sensor
const int irSensor = 8;

void setup() {
  // Set motor control pins as output
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);

  // Set IR sensor pin as input
  pinMode(irSensor, INPUT);

  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Initialize motors to stop
  stopMotors();
}

void loop() {
  // Read the IR sensor value
  int sensorValue = digitalRead(irSensor);

  // Check if the sensor value indicates an obstacle
  if (sensorValue == LOW) { // Assuming LOW means obstacle detected
    Serial.println("Object detected! Moving backward.");
    moveBackward();
  } else {
    Serial.println("No object detected. Moving forward.");
    moveForward();
  }

  delay(500);  // Small delay to debounce sensor input
}

void moveForward() {
  digitalWrite(a1, HIGH);
  digitalWrite(a2, LOW);
  digitalWrite(b1, HIGH);
  digitalWrite(b2, LOW);
}

void moveBackward() {
  digitalWrite(a1, LOW);
  digitalWrite(a2, HIGH);
  digitalWrite(b1, LOW);
  digitalWrite(b2, HIGH);
}

void stopMotors() {
  digitalWrite(a1, LOW);
  digitalWrite(a2, LOW);
  digitalWrite(b1, LOW);
  digitalWrite(b2, LOW);
}
