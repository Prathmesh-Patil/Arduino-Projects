const int blinkPin = 2;     
const int motorPin =  13;      
const int buzzerPin =  12;

long time;

void setup() {
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(blinkPin, INPUT);
  digitalWrite(motorPin, HIGH);
}

void loop() {

  
 if(!digitalRead(blinkPin)){
  
  time=millis();
   while(!digitalRead(blinkPin)){ 
   digitalWrite(buzzerPin, LOW);
   digitalWrite(motorPin, LOW);
   Serial.println("LOW");
   delay(1000);
   }
}
 else {
  if(TimeDelay()>=3)digitalWrite(buzzerPin, HIGH);
  if(TimeDelay()>=4)digitalWrite(motorPin, HIGH);
  Serial.println("HIGH");
  
 }
}

int TimeDelay(){
 long t=millis()-time;
 t=t/1000;
 return t;
}
