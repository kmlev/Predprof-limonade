#define buttonPin 2
#define relayPin 3
int a = 1;
void setup() {
pinMode(buttonPin, INPUT);
pinMode(relayPin, OUTPUT);
}
void loop() {
bool buttonIsUp = digitalRead(buttonPin);
if (buttonIsUp){
  delay(10);
  buttonIsUp = digitalRead(buttonPin);
  if (buttonIsUp){
    if (a == 1){
      digitalWrite(relayPin, HIGH);
      a = 2;
    }
    if (a == 2){
      digitalWrite(relayPin, LOW);
      a = 1;
    }
  }
}
}
