
#include <Keypad.h>
#include <ArrayList.h>
#include <Scheduler.h>

const byte ROWS = 4; // 4 строки
const byte COLS = 4; // 4 столбца
int s = 0;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
}; 
byte rowPins[ROWS] = {11,10, 9, 8}; 
byte colPins[COLS] = {7, 6, 5, 4}; 
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
ArrayList<int> zakazi(ArrayList<int>::DYNAMIC, 4);

void setup()
{
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  int s = 0;
  int D5ml = 100;
  Scheduler.startLoop(MatrixKeyboard);
  
}
void case1(){
    digitalWrite(2, HIGH); // 2 pin - газированная вода

    int D5ml = 100;
    int pomptime1 = 10 * D5ml;
    int pomptime2 = 0;
    int pomptime3 = 0;
    //if(timenow - currentMillis == 0){
          digitalWrite(2, LOW);
    }
//}
void case2(){
    digitalWrite(3, HIGH); // 3 pin - мятный сироп
    int D5ml = 100;
    int pomptime1 = 0;
    int pomptime2 = 2 * D5ml;
    int pomptime3 = 0;
    delay(pomptime2);
    digitalWrite(3, LOW);
}
void case3(){
    digitalWrite(13, HIGH); // 13 pin - апельсиновый сок
    int D5ml = 100;
    int pomptime1 = 0;
    int pomptime2 = 0;
    int pomptime3 = 8 * D5ml;
    delay(pomptime3);
    digitalWrite(13, LOW);
}
void case4(){
  int D5ml = 100;
    digitalWrite(13, HIGH);
    int pomptime1 = 16 * D5ml;
    int pomptime2 = 4 * D5ml;
    int pomptime3 = 0;  
    delay(pomptime2);
    digitalWrite(13, LOW);
}
void case5(){
    int D5ml = 100;
    digitalWrite(13, HIGH);
    int pomptime1 = 16 * D5ml;
    int pomptime2 = 4 * D5ml;
    int pomptime3 = 0;  
    delay(pomptime2);
    digitalWrite(13, LOW);
}



void MatrixKeyboard(){
  int D5ml = 100;
  delay(1000);
  char key = kpd.getKey();
  if(key){
    if((s < 4) || (s == 4)){ 
    if((key == '1') && (s < 4)){ // заказ - газированная вода 50 мл
      s = s + 1;
      zakazi.add(key - 48);
      Serial.print("Номер заказа:");
      Serial.println(s);
      int pomptime1 = 5 * D5ml;
      int pomptime2 = 0;
      int pomptime3 = 0;
      void prepare();
      
    }
     else if((key == '2') && (s < 4)){ // заказ - мятный сироп 10 мл
      s = s + 1;
      zakazi.add(key - 48);
      Serial.print("Номер заказа:");
      Serial.println(s);

    }
    else if((key == '3') && (s < 4)){ // заказ - апельсиновый сок 40 мл
      s = s + 1;
      zakazi.add(key - 48);
      Serial.print("Номер заказа:");
      Serial.println(s);
    }
    else if((key == '4') && (s < 4)){ // заказ - лимонад мятный 80 мл газированной воды 20 мл мятного сиропа
      s = s + 1;
      zakazi.add(key - 48);
      Serial.print("Номер заказа:");
      Serial.println(s);
    }
    else if((key == '5') && (s < 4)){   // заказ - заводной апельсин 30 мл газированной воды 50 мл апельсинового сока
      s = s + 1;
      zakazi.add(key - 48);
      Serial.print("Номер заказа:");
      Serial.println(s);
    }
    else if((key == '6') && (s < 4)){ // заказ - лимонад тройной 35 мл газированной воды 45 мл апельсинового сока 10 мл мятного сиропа
      s = s + 1;
      zakazi.add(key - 48);
      Serial.print("Номер заказа:");
      Serial.println(s);
    }
    else if((key == '*') || (s == '4')){
      for(int i = 0; i < zakazi.size(); i++){
      Serial.print("Был заказан коктейль под номером:");
      Serial.println(zakazi.get(i));
      s = s + 10;
    }
    }
    }
}
}
void prepare(){
  int i;
  case1();

}


