#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_D5 587
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_G5 784
#define NOTE_A5 880

// Define push button pins
const int button1Pin = 2; // Melody 1
const int button2Pin = 3; // Melody 2
const int button3Pin = 4; // Melody 3
const int button4Pin = 5; // Melody 4

// Define the melodies
int melody1[] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_C4}; // Simple melody
int melody2[] = {NOTE_E4, NOTE_F4, NOTE_G4, NOTE_E4}; // Another melody
int melody3[] = {NOTE_G4, NOTE_A4, NOTE_B4, NOTE_G4}; // Third melody
int melody4[] = {NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5}; // Fourth melody

// Define the note durations
int noteDurations[] = {400, 400, 400, 400}; // Duration for each note

void setup() {
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(button3Pin, INPUT_PULLUP);
  pinMode(button4Pin, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(button1Pin) == LOW) {
    playMelody(melody1, noteDurations);
  }
  if (digitalRead(button2Pin) == LOW) {
    playMelody(melody2, noteDurations);
  }
  if (digitalRead(button3Pin) == LOW) {
    playMelody(melody3, noteDurations);
  }
  if (digitalRead(button4Pin) == LOW) {
    playMelody(melody4, noteDurations);
  }
}

void playMelody(int melody[], int durations[]) {
  for (int thisNote = 0; thisNote < 4; thisNote++) {
    tone(8, melody[thisNote], durations[thisNote]);
    delay(durations[thisNote] * 1.30); // Delay for note duration + some
    noTone(8); // Stop the tone
  }
}
