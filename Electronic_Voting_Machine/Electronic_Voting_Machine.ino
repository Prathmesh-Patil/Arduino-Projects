#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd_1(0x27, 16, 2);

#define sw1 2 // Button 1
#define sw2 3 // Button 2
#define sw3 4 // Button 3
#define sw4 5 // Button 4
#define sw5 6 // Button 5 for result
#define buzzer 7 // Buzzer pin

int vote1 = 0;
int vote2 = 0;
int vote3 = 0;
int vote4 = 0;

void setup()
{
  pinMode(sw1, INPUT);
  pinMode(sw2, INPUT);
  pinMode(sw3, INPUT);
  pinMode(sw4, INPUT);
  pinMode(sw5, INPUT);
  pinMode(12, OUTPUT); // Green LED for voting
  pinMode(13, OUTPUT); // Red LED for result
  pinMode(buzzer, OUTPUT); // Buzzer for sound

  lcd_1.begin(16, 2);
  lcd_1.backlight();
  lcd_1.setCursor(0, 0);
  lcd_1.print("     EVM ");
  lcd_1.setCursor(0, 1);
  lcd_1.print("Circuit Design ");
  delay(1000);
  
  digitalWrite(sw1, HIGH);
  digitalWrite(sw2, HIGH);
  digitalWrite(sw3, HIGH);
  digitalWrite(sw4, HIGH);
  digitalWrite(sw5, HIGH);
  
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("RG");
  lcd_1.setCursor(4, 0);
  lcd_1.print("BG");
  lcd_1.setCursor(8, 0);
  lcd_1.print("YG");
  lcd_1.setCursor(12, 0);
  lcd_1.print("GG");
}

void loop()
{
  lcd_1.setCursor(0, 0);
  lcd_1.print("RG");
  lcd_1.setCursor(1, 1);
  lcd_1.print(vote1);
  lcd_1.setCursor(4, 0);
  lcd_1.print("BG");
  lcd_1.setCursor(5, 1);
  lcd_1.print(vote2);
  lcd_1.setCursor(8, 0);
  lcd_1.print("YG");
  lcd_1.setCursor(9, 1);
  lcd_1.print(vote3);
  lcd_1.setCursor(12, 0);
  lcd_1.print("GG");
  lcd_1.setCursor(13, 1);
  lcd_1.print(vote4);

  // RG Vote
  if (digitalRead(sw1) == 0)
  { 
    vote1++;
    digitalWrite(12, HIGH); // Turn on Green LED
    tone(buzzer, 1000); // Activate buzzer with 1kHz frequency
    delay(500);
    digitalWrite(12, LOW); // Turn off Green LED
    noTone(buzzer); // Turn off buzzer
    while (digitalRead(sw1) == 0); // Wait until button is released
    delay(1000);
  }

  // BG Vote
  if (digitalRead(sw2) == 0)
  {
    vote2++;
    digitalWrite(12, HIGH); // Turn on Green LED
    tone(buzzer, 1000); // Activate buzzer with 1kHz frequency
    delay(500);
    digitalWrite(12, LOW); // Turn off Green LED
    noTone(buzzer); // Turn off buzzer
    while (digitalRead(sw2) == 0); // Wait until button is released
    delay(1000);
  }

  // YG Vote
  if (digitalRead(sw3) == 0)
  {
    vote3++;
    digitalWrite(12, HIGH); // Turn on Green LED
    tone(buzzer, 1000); // Activate buzzer with 1kHz frequency
    delay(500);
    digitalWrite(12, LOW); // Turn off Green LED
    noTone(buzzer); // Turn off buzzer
    while (digitalRead(sw3) == 0); // Wait until button is released
    delay(1000);
  }

  // GG Vote
  if (digitalRead(sw4) == 0)
  {
    vote4++;
    digitalWrite(12, HIGH); // Turn on Green LED
    tone(buzzer, 1000); // Activate buzzer with 1kHz frequency
    delay(500);
    digitalWrite(12, LOW); // Turn off Green LED
    noTone(buzzer); // Turn off buzzer
    while (digitalRead(sw4) == 0); // Wait until button is released
    delay(1000);
  }

  // Show Result
  if (digitalRead(sw5) == 0)
  {
    digitalWrite(13, HIGH); // Turn on Red LED for result
    int totalVotes = vote1 + vote2 + vote3 + vote4;

    if (totalVotes > 0)
    {
      lcd_1.clear();
      if (vote1 > vote2 && vote1 > vote3 && vote1 > vote4)
        lcd_1.print("RG Wins");
      else if (vote2 > vote1 && vote2 > vote3 && vote2 > vote4)
        lcd_1.print("BG Wins");
      else if (vote3 > vote1 && vote3 > vote2 && vote3 > vote4)
        lcd_1.print("YG Wins");
      else if (vote4 > vote1 && vote4 > vote2 && vote4 > vote3)
        lcd_1.print("GG Wins");
      else
        lcd_1.print("Tie or No Result");

      delay(5000);
      lcd_1.clear();
    }
    else
    {
      lcd_1.clear();
      lcd_1.print("No Voting...");
      delay(5000);
      lcd_1.clear();
    }

    // Reset Votes
    vote1 = 0;
    vote2 = 0;
    vote3 = 0;
    vote4 = 0;
    totalVotes = 0;
    digitalWrite(13, LOW); // Turn off Red LED after result
  }
}
