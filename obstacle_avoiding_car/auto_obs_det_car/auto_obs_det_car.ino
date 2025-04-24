#include <Servo.h>
#include <Ultrasonic.h>
Servo servo;
Ultrasonic sensor(12, 13);
#define in1 8
#define in2 7
#define in3 2
#define in4 4
#define enA 6
#define enB 5
int forward_distance = 0;
int left_distance = 0;
int right_distance = 0;
int M1_Speed = 80;  // speed of motor 1 0-255
int M2_Speed = 90;  // speed of motor 2
void setup() {
  servo.attach(9);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
}

void loop() {

  forward_distance = sensor.read();

  if ((forward_distance < 45) && (forward_distance > 0)) {
    backward();
    delay(200);
    Stop();
    delay(200);
    servo.write(0);
    delay(300);
    left_distance = sensor.read();
    delay(300);
    servo.write(180);
    delay(300);
    right_distance = sensor.read();
    delay(300);


    if (left_distance >= right_distance) {
      left();
      servo.write(90);
      delay(300);
    } else {
      right();
      servo.write(90);
      delay(300);
    }

  } else {
    forward();
  }
  delay(500);
}
void forward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enA, M1_Speed);
  analogWrite(enB, M2_Speed);
}

void backward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enA, 60);
  analogWrite(enB, 65);
}

void left() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enA, 60);
  analogWrite(enB, 65);
}

void right() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enA, 60);
  analogWrite(enB, 65);
}

void Stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}