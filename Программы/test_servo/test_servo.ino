#include <Servo.h>
Servo myservo;
void setup() {
  myservo.attach(3);
  Serial.begin(9600);
}
uint32_t tmr;   // переменная таймера
int val = 0;    // переменная яркости
int dir = 2;    // скорость и направление яркости
void loop() {
  // асинхронный таймер на миллис
  if (millis() - tmr >= 100) {
    tmr = millis();
    val += dir;                             // прибавляем скорость
    if (val >= 180|| val <= 0) dir = -dir;  // разворачиваем
    myservo.write(val);                     // применяем
    Serial.println(val);
    
  }
}
