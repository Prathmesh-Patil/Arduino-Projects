int motor1pin1 = 9;
int motor1pin2 = 6;
 
int motor2pin1 = 5;
int motor2pin2 = 3;
 
void setup() {
  // put your setup code here, to run once:
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
 
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
}
 
void loop() {
  // put your main code here, to run repeatedly:
 
  //  //Controlling speed (0 = off and 255 = max speed):
  // analogWrite(9, 200); //ENA pin
  // analogWrite(10, 200); //ENB pin
 
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
 
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  delay(1000);
 
 // Stop before moving back
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
 
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
  delay(1000); // Pause
 
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
 
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
  delay(1000);
 
   // Stop before moving left
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
  delay(1000); // Pause
 
   // Move left
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
 
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  delay(1000); // Adjust delay as needed
 
 // Stop before moving right
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
 
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
  delay(1000); // Pause
 
  // Move right
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
 
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
  delay(1000); // Adjust delay as needed
  
  // Stop
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
 
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
  delay(1000); // Pause

}