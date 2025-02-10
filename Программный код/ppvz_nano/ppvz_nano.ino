/*
 Подсистема приема и выдачи заказов
 (С) Школа 1103, г. Москва
 */

#include <SimpleKeypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


// размеры клавиатуры
#define KP_ROWS 4
#define KP_COLS 4
#define PLACES 4 // количество стаканов

// пины подключения клавиатуры
byte colPins[KP_COLS] = {5, 4, 3, 2};
byte rowPins[KP_ROWS] = {9, 8, 7, 6};

// массив имён кнопок
char keys[KP_ROWS][KP_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
// экран
LiquidCrystal_I2C lcd(0x27, 16, 2);

byte order[PLACES] = {0}; // массив заказа
byte cnt = 0; // счетчик


// создаём клавиатуру
SimpleKeypad pad((char*)keys, rowPins, colPins, KP_ROWS, KP_COLS);

byte check_cnt(){

      if (cnt >= PLACES)  {
      lcd.clear();
      lcd.print("Error!!!");
      lcd.setCursor(0, 1);
      lcd.print("Press *");
      return 1;
     }
     else
      {
      return 0;
      }
}
void SendData(){
    if (cnt > 0) {
    // выводим в порт
      for (byte i = 0; i<PLACES; i++){
      // Serial.print(i);
       Serial.print(order[i]);
     //  Serial.print(" ");
       order[i]= 0;
      }
       Serial.println("");
  }
  cnt = 0;
  }

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW); 
  Serial.begin(9600);
  lcd.init(); // Инициализируем экран
  lcd.backlight();
  lcd.clear();
  lcd.print("From 1 to 6:");
  lcd.setCursor(0, 1); // устанавливаем курсор на начало второй строки
  lcd.cursor(); // выводим курсор
}

void loop() {
  // получить текущую нажатую клавишу
  // вернёт 0 символ, если ничего не нажато
  char key = pad.getKey();

  // если кнопка нажата (не 0 символ)
  switch (key) {
    case '*':
    for (byte i = 0; i<PLACES; i++){
       order[i]= 0;
      }
    cnt= 0;
    lcd.clear();
    lcd.print("From 1 to 6:");
    lcd.setCursor(0, 1); // устанавливаем курсор на начало второй строки
    break;
    
    case '#':
    SendData();
    lcd.clear();
    lcd.print("From 1 to 6:");
    lcd.setCursor(0, 1); // устанавливаем курсор на начало второй строки
    break;
    
    case '1':
    if (check_cnt() == 1){
      break;
    }
    order[cnt] = 1;
    cnt++;
    lcd.print("1");
    break;

    case '2':
    if (check_cnt() == 1){
      break;
    }
    order[cnt] = 2;
    cnt++;
    lcd.print("2");
    break;

    case '3':
    if (check_cnt() == 1){
      break;
    }
    order[cnt] = 3;
    cnt++;
    lcd.print("3");
    break;

    case '4':
    if (check_cnt() == 1){
      break;
    }
    order[cnt] = 4;
    cnt++;
    lcd.print("4");
    break;

    case '5':
    if (check_cnt() == 1){
      break;
    }
    order[cnt] = 5;
    cnt++;
    lcd.print("5");
    break;

    case '6':
    if (check_cnt() == 1){
      break;
    }
    order[cnt] = 6;
    cnt++;
    lcd.print("6");
    break;
  }

  

}
