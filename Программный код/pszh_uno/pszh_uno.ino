/*
 Подсистема смешивания жидкостей
 (С) Школа 1103, г.Москва
 */
// #include <Servo.h>
#include "ServoSmooth.h" 
#include <TaskScheduler.h>


#define STACK 4 // количество стаканов
#define RELE1_PIN 2 // пин реле 1
#define RELE2_PIN 3 // пин реле 2
#define RELE3_PIN 4 // пин реле 3
#define GLASS1_PIN 5 // пин выключатель 1
#define GLASS2_PIN 6 // пин выключатель 2
#define GLASS3_PIN 7 // пин выключатель 3
#define GLASS4_PIN 8 // пин выключатель 4
#define CRAN_PIN 9 // сервопривод крана
#define SERVO_PIN 10 // сервопривод
#define STOP_PIN 11 // пин выключатель останова
#define TIME_5ML 500 // время в мс для 5 мл
# define TOL 2 // точность установки угла

ServoSmooth servoCran(180);   // создали с указанием макс. угла серво
ServoSmooth servoTable(180);   // создали с указанием макс. угла серво

String strData = ""; // для данных с Serial
boolean recievedFlag = false; // флаг получения данных на Serial
String tempStr = "";
byte state = 0; // текущее состояние
byte total = 0; // всего позиций в заказе 
byte recipe[STACK] = {0}; // полученный заказ
byte glass[STACK] = {0}; // наличие стаканов
//byte glass[] = {1,1,1,1};
byte real_glass = 0; // рельное количество стаканов
int pump_position[4] = {45, 90, 135, 170}; // положение сервомотора над стаканами
byte cnt = 0; // номер стакана
bool isGlass =false;
bool stopBtn = false; // кнопка останова
bool startFlag = false; // флаг старта
int delta = 0; // рассогласование угла

// прототип функций
void buttonclick();   //задаем прототип для нажатия кнопки
void servoTick();   //задаем прототип для серво


// Создаем объекты 
Scheduler userScheduler;   // планировщик

Task taskButtonclick(TASK_MILLISECOND * 50 , TASK_FOREVER, &buttonclick);   // задание для кнопок
Task taskServo(TASK_MILLISECOND * 20 , TASK_FOREVER, &servoTick);   // задание для серво


void setup() {
 Serial.begin(9600);
 // конфигурация портов
 pinMode(RELE1_PIN, OUTPUT);
 pinMode(RELE2_PIN, OUTPUT);
 pinMode(RELE3_PIN, OUTPUT);
 digitalWrite(RELE1_PIN, LOW);
 digitalWrite(RELE2_PIN, LOW);
 digitalWrite(RELE3_PIN, LOW);
 pinMode(GLASS1_PIN, INPUT_PULLUP);
 pinMode(GLASS2_PIN, INPUT_PULLUP);
 pinMode(GLASS3_PIN, INPUT_PULLUP);
 pinMode(GLASS4_PIN, INPUT_PULLUP);
 
 pinMode(STOP_PIN, INPUT_PULLUP);

servoCran.attach(CRAN_PIN);  // стартовый угол 0 градусов
servoCran.smoothStart();  // "плавно" движемся к нему
servoCran.setSpeed(50); // скорость

servoTable.attach(SERVO_PIN);  // стартовый угол 0 градусов
servoTable.smoothStart();  // "плавно" движемся к нему
servoTable.setSpeed(40); // скорость

// добавляем задания в обработчик
userScheduler.addTask(taskButtonclick);
userScheduler.addTask(taskServo);


// запускаем
taskButtonclick.enable();
taskServo.enable();

}

//прием данных с serial
String recieveData(){
if (Serial.available() > 0) {  // если есть что-то на вход
    strData = "";                // очистить строку
    while (Serial.available() > 0) {
      // пока идут данные
      strData += (char)Serial.read();  // получаем данные
      delay(2);                        // обязательно задержка, иначе вылетим из цикла раньше времени
    }
    recievedFlag = true;  // поднять флаг что получили данные
  }

 if (recievedFlag) {
      recievedFlag = false;  // данные приняты
      return strData;
     }
  else
     return "";

}

// инициализиция стаканов
byte init_glass(){
  byte total_glass = 0;
  for (int i = 0; i<STACK; i++){
    if (glass[i]== 1)
      total_glass++;
  }
  return total_glass;
}

// рецепты (номер рецепта, номер стакана)
void make_recipe(byte num, byte control){
  Serial.print("num=");
  Serial.println(num);
  Serial.print("control=");
  Serial.println(control);

unsigned long delta = 0; // осталось времени до конца
bool isEnd = false; // выход из внешнего цикла
bool isFirst = true; // для двойного рецепта
bool isSecond = false; // для двойного рецепта
// bool isAbsent = false; // нет стакана
unsigned long start_time = millis(); // время запуска насоса

while (true){
  userScheduler.execute(); // обновляем задания планировщика, т.к. вышли из основного loop()
   if (stopBtn)
       isEnd = true; // кнопка останова
  
 //  Serial.println("glass[control]");
 //  Serial.println(glass[control]); 
  switch (num) { 
   case 1:
// Газированная вода (50 мл.) реле 1
    if (glass[control] == 0){
      digitalWrite(RELE1_PIN, LOW);
      start_time = millis() - delta;
     }
    else
     {
      digitalWrite(RELE1_PIN, HIGH);
      delta = millis()- start_time;
     }
    
    if (delta > TIME_5ML*10){
      digitalWrite(RELE1_PIN, LOW);
      isEnd = true;
    }
   break;

   case 2:
// Мятный сироп (10 мл.) реле 2
    if (glass[control] == 0){
      digitalWrite(RELE2_PIN, LOW);
      start_time = millis() - delta;
     }
    else
     {
      digitalWrite(RELE2_PIN, HIGH);
      delta = millis()- start_time;
     }
    
    if (delta > TIME_5ML*2){
      digitalWrite(RELE2_PIN, LOW);
      isEnd = true;
    }
   break;

   case 3:
// Апельсиновый сок (40 мл.) реле 3
    if (glass[control] == 0){
      digitalWrite(RELE3_PIN, LOW);
      start_time = millis() - delta;
     }
    else
     {
      digitalWrite(RELE3_PIN, HIGH);
      delta = millis()- start_time;
     }
    
    if (delta > TIME_5ML*8){
      digitalWrite(RELE3_PIN, LOW);
      isEnd = true;
    }
   break;

   case 4:
// Лимонад “Мятный” (80 мл. газированной воды + 20 мл. мятного сиропа). реле 1 и реле 2
 if (isFirst){    
     if (glass[control] == 0){
      digitalWrite(RELE1_PIN, LOW);
      start_time = millis() - delta;
     }
    else
     {
      digitalWrite(RELE1_PIN, HIGH);
      delta = millis()- start_time;
     }
    
    if (delta > TIME_5ML*16){
      digitalWrite(RELE1_PIN, LOW);
       isFirst = false;
       start_time = millis();
    }
}   

if (!isFirst){
     if (glass[control] == 0){
      digitalWrite(RELE2_PIN, LOW);
      start_time = millis() - delta;
     }
    else
     {
      digitalWrite(RELE2_PIN, HIGH);
      delta = millis()- start_time;
     }
    
    if (delta > TIME_5ML*4){
      digitalWrite(RELE2_PIN, LOW);
      isEnd = true;
    }
}    

   break;

   case 5:
// Лимонад “Заводной апельсин” (30 мл. газированной воды + 50 мл. апельсинового сока).реле 1 и реле 3
   
 if (isFirst){    
     if (glass[control] == 0){
      digitalWrite(RELE1_PIN, LOW);
      start_time = millis() - delta;
     }
    else
     {
      digitalWrite(RELE1_PIN, HIGH);
      delta = millis()- start_time;
     }
    
    if (delta > TIME_5ML*6){
      digitalWrite(RELE1_PIN, LOW);
       isFirst = false;
       start_time = millis();
    }
}

if (!isFirst){
     if (glass[control] == 0){
      digitalWrite(RELE3_PIN, LOW);
      start_time = millis() - delta;
     }
    else
     {
      digitalWrite(RELE3_PIN, HIGH);
      delta = millis()- start_time;
     }
    
    if (delta > TIME_5ML*10){
      digitalWrite(RELE3_PIN, LOW);
      isEnd = true;
    }
} 
   break;

   case 6:
// f. Лимонад ‘Тройной” (35 мл. газированной воды + 45 мл. апельсинового сока + 10 мл.
// мятного сиропа) реле 1 реле 3 реле 2
    
 if (isFirst){    
     if (glass[control] == 0){
      digitalWrite(RELE1_PIN, LOW);
      start_time = millis() - delta;
     }
    else
     {
      digitalWrite(RELE1_PIN, HIGH);
      delta = millis()- start_time;
     }
    
    if (delta > TIME_5ML*7){
      digitalWrite(RELE1_PIN, LOW);
       isFirst = false;
       isSecond = true;
       start_time = millis();
    }
}   

if (isSecond){
     if (glass[control] == 0){
      digitalWrite(RELE3_PIN, LOW);
      start_time = millis() - delta;
     }
    else
     {
      digitalWrite(RELE3_PIN, HIGH);
      delta = millis()- start_time;
     }
    
    if (delta > TIME_5ML*9){
      digitalWrite(RELE3_PIN, LOW);
      isSecond = false;
      start_time = millis();      
    }
}

if (!isFirst && !isSecond){
     if (glass[control] == 0){
      digitalWrite(RELE2_PIN, LOW);
      start_time = millis() - delta;
     }
    else
     {
      digitalWrite(RELE2_PIN, HIGH);
      delta = millis()- start_time;
     }
    
    if (delta > TIME_5ML*2){
      digitalWrite(RELE2_PIN, LOW);
      isEnd = true;
    }
}     

   break;
  }
  if (isEnd)
    break;
 }
  Serial.println("FINISH!");
}

void loop() {
 //запуск планировщика заданий
userScheduler.execute();
//Serial.println(glass[0]);


switch (state) {   // автомат состояний
 case  0: // получение рецепта от uno
  tempStr = recieveData();
  if (tempStr != "") {
    Serial.println("yes");
    Serial.println(tempStr);

    for (int i = 0; i<STACK; i++){
      recipe[i] = tempStr.charAt(i) - '0';
      }

    /* Вывод переменных
  Serial.print("Рецепт 1: ");
  Serial.println(recipe[0]);
  Serial.print("Рецепт 2: ");
  Serial.println(recipe[1]);
  Serial.print("Рецепт 3: ");
  Serial.println(recipe[2]);
  Serial.print("Рецепт 4: ");
  Serial.println(recipe[3]);*/
   state = 1; 
    }
  break;

  case 1: // основной алгоритм
  
  // повернем стол

    servoTable.setTargetDeg(0);
    startFlag = true;  
    while (startFlag){
      userScheduler.execute(); // обновляем задания планировщика, т.к. вышли из основного loop()
      delta = servoTable.getCurrentDeg();
        if (abs(delta) <= TOL) {
           Serial.println("destination table angle  done!");
           startFlag = false;
           break;
           }
        }
  
  cnt = 0;
  for (int i = 0; i<STACK; i++){
    if (recipe[i] == 0)
      break;
    total++;
  }

   // если стаканов меньше, чем в рецепте будем наливать только в те, что есть
    real_glass = init_glass();
    if (real_glass < total)
       total = real_glass;
    Serial.print("real_glass=");
    Serial.println(real_glass);
    Serial.print("total=");
    Serial.println(total);
   // основной цикл для заданного количества стаканов
   isGlass= false;
    for (byte i = 0; i<total; i++){

      for (byte j= 0; j<STACK; j++){
        if (glass[cnt] == 0){
           cnt++;
        }
        if (cnt > STACK){
          isGlass= false;
          break;
        }  
        if (glass[cnt] == 1){
          isGlass= true;
          break;
        }
      
      }
       if (isGlass){
        Serial.print("i=");
        Serial.println(i);
        Serial.print("cnt=");
        Serial.println(cnt);
        
        // устанавливаем серво на нужный угол
        servoCran.setTargetDeg(pump_position[cnt]);
        startFlag = true;
        Serial.print("angle=");
        Serial.println(pump_position[cnt]);
            while (startFlag){
              userScheduler.execute(); // обновляем задания планировщика, т.к. вышли из основного loop()
              delta = servoCran.getCurrentDeg()- pump_position[cnt];
               if (abs(delta) <= TOL) {
                 Serial.println("destination angle=0  done!");
                 startFlag = false;
                 break;
                }
            }
        
        make_recipe(recipe[i], cnt);
       // Serial.print("glass[0]=");
      //  Serial.println(glass[0]);
        cnt++;
        if (stopBtn) {
          // кнопка останов
          break;
          }
        }
   servoCran.setTargetDeg(pump_position[0]); // на первую позицию
   startFlag = true;
    while (startFlag){
      userScheduler.execute(); // обновляем задания планировщика, т.к. вышли из основного loop()
      delta = servoCran.getCurrentDeg()- pump_position[0];
        if (abs(delta) <= TOL) {
          Serial.println("destination angle  done!");
              startFlag = false;
            break;
           }
      }
   
   
   }
  
  // закончили, выход в режим ожидания приёма заказа
  if (stopBtn)
    state = 0;
  else
    state = 2;
    
  total = 0; 
  Serial.println("state 1 finished!");
  break;

  case 2: // выдача
  Serial.println("state 2 start");
   
  servoTable.setTargetDeg(180);
  startFlag = true;  
    while (startFlag){
      userScheduler.execute(); // обновляем задания планировщика, т.к. вышли из основного loop()
      delta = servoTable.getCurrentDeg()- 180;
        if (abs(delta) <= TOL) {
           Serial.println("destination table angle  done!");
           startFlag = false;
           break;
           }
        }
  
  state = 0;
  Serial.println("state 2 finished!");
  break;

}

}

void buttonclick(){
  //ПОСТАВИТЬ ИНВЕРСИЮ ПОСЛЕ ПОДКЛЮЧЕНИЯ ДАТЧИКОВ!!!
  glass[0] = !digitalRead(GLASS1_PIN);
  glass[1] = !digitalRead(GLASS2_PIN);
  glass[2] = !digitalRead(GLASS3_PIN);
  glass[3] = !digitalRead(GLASS4_PIN);
  stopBtn =  !digitalRead(STOP_PIN);
}



void servoTick(){
servoTable.tickManual();   // двигаем  серво
servoCran.tickManual();   // двигаем  серво
}
