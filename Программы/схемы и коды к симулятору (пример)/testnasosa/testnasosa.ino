void setup() {
  pinMode(7, OUTPUT);
}

void loop() {
  int i;
  for(i = 0; i < 4; i++){
  digitalWrite(7, HIGH);
  delay(1000);
  digitalWrite(7, LOW);
  delay(3000);
  }
  for(i = 0; i < 4; i++){
    digitalWrite(7, HIGH);
    delay(2000);
    digitalWrite(7, LOW);
    delay(3000);
  }

}
