#include <Keypad.h>

const int buzzerPin = 11;
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; // connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; // connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  char key = keypad.getKey();
  
  if (key) {
    switch (key) {
      case '1':
        playTone(262); // C4
        break;
      case '2':
        playTone(294); // D4
        break;
      case '3':
        playTone(330); // E4
        break;
      case '4':
        playTone(349); // F4
        break;
      case '5':
        playTone(392); // G4
        break;
      case '6':
        playTone(440); // A4
        break;
      case '7':
        playTone(494); // B4
        break;
      case '8':
        playTone(523); // C5
        break;
      case '9':
        playTone(587); // D5
        break;
      case '0':
        playTone(659); // E5
        break;
      case 'A':
        playTone(698); // F5
        break;
      case 'B':
        playTone(784); // G5
        break;
      case 'C':
        playTone(880); // A5
        break;
      case 'D':
        playTone(988); // B5
        break;
      case '*':
        playTone(1047); // C6
        break;
      case '#':
        // Do something else or stop the tone
        break;
    }
  }
}

void playTone(int frequency) {
  tone(buzzerPin, frequency);
  delay(200); // Adjust this value for the duration of the note
  noTone(buzzerPin);
}
