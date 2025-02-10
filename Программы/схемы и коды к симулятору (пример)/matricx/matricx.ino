#include <Keypad.h>
#include <ArrayList.h> 

const byte ROWS = 4; // 4 строки
const byte COLS = 4; // 4 столбца
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
}; 
byte rowPins[ROWS] = {11,10, 9, 8}; 
byte colPins[COLS] = {7, 6, 5, 4}; 
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
 
void setup()
{
  pinMode(2, OUTPUT);
  Serial.begin(9600);
}
  
void loop(){
  ArrayList<int> zakazi(ArrayList<int>::DYNAMIC, 0);
  int i;
  int D5ml = 100;
  char key = kpd.getKey();                 // считываем нажатую кнопку
  int s = 0;
  if(key){
    while(key != '*' || s < 4){
    if(key == '1'){ // заказ - газированная вода 50 мл
      zakaz1();
      s = s + 1;
      ArrayList<int> zakazi(ArrayList<int>::DYNAMIC, s);
      zakazi.add(int(key));
    }
     else if(key == '2' || s < 4){ // заказ - мятный сироп 10 мл
      zakaz2();
      s = s + 1;
      ArrayList<int> zakazi(ArrayList<int>::DYNAMIC, s);
      zakazi.add(int(key));
    }
    else if(key == '3' || s < 4){ // заказ - апельсиновый сок 40 мл
      zakaz3();
      s = s + 1;
      ArrayList<int> zakazi(ArrayList<int>::DYNAMIC, s);
      zakazi.add(int(key));
    }
    else if(key == '4' || s < 4){ // заказ - лимонад мятный 80 мл газированной воды 20 мл мятного сиропа
      zakaz4();
      s = s + 1;
      ArrayList<int> zakazi(ArrayList<int>::DYNAMIC, s);
      zakazi.add(int(key));
    }
    else if(key == '5' || s < 4){   // заказ - заводной апельсин 30 мл газированной воды 50 мл апельсинового сока
      zakaz5();
      s = s + 1;
      ArrayList<int> zakazi(ArrayList<int>::DYNAMIC, s);
      zakazi.add(int(key));
    }
    else if(key == '6' || s < 4){ // заказ - лимонад тройной 35 мл газированной воды 45 мл апельсинового сока 10 мл мятного сиропа
      zakaz6();
      s = s + 1;
      ArrayList<int> zakazi(ArrayList<int>::DYNAMIC, s);
      zakazi.add(int(key));
    }
    }
    for(int i = 0; i < zakazi.size(); i++){
    Serial.println(zakazi.get(i));
    }
}
}
void zakaz1(){
    int D5ml = 100;
    digitalWrite(2, HIGH); // 2 pin - газированная вода
    delay(10 * D5ml);
    digitalWrite(2, LOW);
}
void zakaz2(){
    int D5ml = 100;
    digitalWrite(3, HIGH); // 3 pin - мятный сироп
    delay(D5ml);
    digitalWrite(3, LOW);
}
void zakaz3(){
    int D5ml = 100;
    digitalWrite(13, HIGH); // 4 pin - апельсиновый сок
    delay(8 * D5ml);
    digitalWrite(13, LOW);
}
void zakaz4(){
    int D5ml = 100;
    digitalWrite(2, HIGH);
    delay(16 * D5ml);
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    delay(4 * D5ml);
    digitalWrite(3, LOW);  
}
void zakaz5(){
    int D5ml = 100;
    digitalWrite(2, HIGH);
    delay(6 * D5ml);
    digitalWrite(2, LOW);
    digitalWrite(13, HIGH);
    delay(10 * D5ml);
    digitalWrite(13, LOW);
}
void zakaz6(){
    int D5ml = 100;
    digitalWrite(2, HIGH);
    delay(7 * D5ml);
    digitalWrite(2, LOW);
    digitalWrite(13, HIGH);
    delay(9 * D5ml);
    digitalWrite(13, LOW);
    digitalWrite(3, HIGH);
    delay(2 * D5ml);
    digitalWrite(3, LOW);
}