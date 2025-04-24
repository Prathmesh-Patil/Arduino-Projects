#include <Servo.h> //Install this library 

Servo tap_servo;

int sensor_pin = 5;   //Connect D5 of Arduino 
int tap_servo_pin =4; //Connect D4 of Arduino 
int val;

void setup(){
  pinMode(sensor_pin,INPUT);
  tap_servo.attach(tap_servo_pin);
  
}

void loop(){
  val = digitalRead(sensor_pin);

  if (val==0)
  {tap_servo.write(0);
  }
  if (val==1)
  {tap_servo.write(90); //If you want you can increase & Decrease servo rotation 
    }
}
