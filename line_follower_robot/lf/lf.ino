int mot1 = 9;
int mot2 = 6;
int mot3 = 5;
int mot4 = 3;

int left = 13;
int right = 12;

int Left = 0;
int Right = 0;

void LEFT(void);
void RIGHT(void);
void STOP(void);

void setup() {
  pinMode(mot1, OUTPUT);
  pinMode(mot2, OUTPUT);
  pinMode(mot3, OUTPUT);
  pinMode(mot4, OUTPUT);

  pinMode(left, INPUT);
  pinMode(right, INPUT);

  digitalWrite(left, HIGH);
  digitalWrite(right, HIGH);
}

void loop() {

  analogWrite(mot1, 255);
  analogWrite(mot2, 0);
  analogWrite(mot3, 255);
  analogWrite(mot4, 0);

  while (1) {
    Left = digitalRead(left);
    Right = digitalRead(right);

    if (Left == 0 && Right == 1)
      LEFT();
    else if (Right == 0 && Left == 1)
      RIGHT();
  }
}

void LEFT(void) {
  analogWrite(mot3, 0);
  analogWrite(mot4, 30);

  while (Left == 0) {
    Left = digitalRead(left);
    Right = digitalRead(right);
    if (Right == 0) {
      int lprev = Left;
      int rprev = Right;
      STOP();
      while ((lprev == Left) && (rprev == Right)) {
        Left = digitalRead(left);
        Right = digitalRead(right);
      }
    }
    analogWrite(mot1, 255);
    analogWrite(mot2, 0);
  }
  analogWrite(mot3, 255);
  analogWrite(mot4, 0);
}

void RIGHT(void) {
  analogWrite(mot1, 0);
  analogWrite(mot2, 30);

  while (Right == 0) {
    Left = digitalRead(left);
    Right = digitalRead(right);
    if (Left == 0) {
      int lprev = Left;
      int rprev = Right;
      STOP();
      while ((lprev == Left) && (rprev == Right)) {
        Left = digitalRead(left);
        Right = digitalRead(right);
      }
    }
    analogWrite(mot3, 255);
    analogWrite(mot4, 0);
  }
  analogWrite(mot1, 255);
  analogWrite(mot2, 0);
}

void STOP(void) {
  analogWrite(mot1, 0);
  analogWrite(mot2, 0);
  analogWrite(mot3, 0);
  analogWrite(mot4, 0);
}

// int mot1 = 9;
// int mot2 = 6;
// int mot3 = 5;
// int mot4 = 3;

// int left = 13;
// int right = 12;

// void setup() {
//   pinMode(mot1, OUTPUT);
//   pinMode(mot2, OUTPUT);
//   pinMode(mot3, OUTPUT);
//   pinMode(mot4, OUTPUT);

//   pinMode(left, INPUT);
//   pinMode(right, INPUT);

//   digitalWrite(left, HIGH); // Activate internal pull-up resistor
//   digitalWrite(right, HIGH); // Activate internal pull-up resistor
// }

// void loop() {
//   int Left = digitalRead(left);
//   int Right = digitalRead(right);

//   // Move forward
//   if (Left == HIGH && Right == HIGH) {
//     digitalWrite(mot1, HIGH);
//     digitalWrite(mot2, LOW);
//     digitalWrite(mot3, HIGH);
//     digitalWrite(mot4, LOW);
//   }
//   // Turn left
//   else if (Left == LOW && Right == HIGH) {
//     digitalWrite(mot1, HIGH);
//     digitalWrite(mot2, LOW);
//     digitalWrite(mot3, LOW);
//     digitalWrite(mot4, LOW);
//   }
//   // Turn right
//   else if (Left == HIGH && Right == LOW) {
//     digitalWrite(mot1, LOW);
//     digitalWrite(mot2, LOW);
//     digitalWrite(mot3, HIGH);
//     digitalWrite(mot4, LOW);
//   }
//   // Stop
//   else {
//     digitalWrite(mot1, LOW);
//     digitalWrite(mot2, LOW);
//     digitalWrite(mot3, LOW);
//     digitalWrite(mot4, LOW);
//   }
// }

