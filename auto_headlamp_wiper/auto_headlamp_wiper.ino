#include<Servo.h>
Servo motor;
int LDR = 5;
int LED = 4;
int rain = 6;
void setup()
{
  motor.attach(9);
  pinMode(LDR, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(rain, INPUT);
 
}
void loop()
{
  lamp();
  wiper();
}
void wiper()
{
  int drop = analogRead(rain);
  if(drop >= 450)
  {
    motor.write(0);
    delay(100);
    motor.write(180);
    delay(100);
  }
  else if(drop<450)
  {
    motor.write(0);
  }
}
void lamp()
{
  int sensor = digitalRead(LDR);
  if(sensor == 1)
  {
    digitalWrite(LED, HIGH);
  }
  else
  {
    digitalWrite(LED, LOW);
  }