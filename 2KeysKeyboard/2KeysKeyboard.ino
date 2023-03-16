#include "DigiKeyboard.h"

#define KEYPAD_1                (  89  | 0xF000 )
#define KEYPAD_2                (  90  | 0xF000 )
#define KEYPAD_3                (  91  | 0xF000 )
#define KEYPAD_4                (  92  | 0xF000 )
#define KEYPAD_5                (  93  | 0xF000 )
#define KEYPAD_6                (  94  | 0xF000 )
#define KEYPAD_7                (  95  | 0xF000 )
#define KEYPAD_8                (  96  | 0xF000 )
#define KEYPAD_9                (  97  | 0xF000 )
#define KEYPAD_0                (  98  | 0xF000 )

#define LONGPRESSTIME 2000 // время долгого нажатия в миллисекундах
#define hardware_button_A 0  //pin 0
#define hardware_button_B 2  //pin 1

uint32_t pressTimer;
bool is_hardware_button_A_pressed;
bool is_hardware_button_B_pressed;
bool is_once_button_pressed;

void setup() {
   pinMode(hardware_button_A, INPUT);
   pinMode(hardware_button_B, INPUT);
}

void loop() {
  // this is generally not necessary but with some older systems it seems to
  // prevent missing the first character after a delay:
  //DigiKeyboard.sendKeyStroke(0);
  
  // Type out this string letter by letter on the computer (assumes US-style
  // keyboard)
  //DigiKeyboard.println("button_A_is_pressed");
  
  pressTimer = millis();
  is_hardware_button_A_pressed = false;
  is_hardware_button_B_pressed = false;
  is_once_button_pressed = false;

  while (digitalRead(hardware_button_A)== HIGH){ //фиксируем нажатие кнопки "А" и считаем длительность, если более 2 секунд, то отправляем событие и ждем отпускания
    is_hardware_button_A_pressed = true;
    if (!is_once_button_pressed){
      if (millis()-pressTimer>LONGPRESSTIME){
        is_once_button_pressed = true;
        pressKey(KEYPAD_3);
      }
    }
  }
  if (!is_once_button_pressed && is_hardware_button_A_pressed && millis()-pressTimer<LONGPRESSTIME){ //фиксируем одиночное нажатие кнопки "А" менее LONGPRESSTIME
        is_once_button_pressed = true;
        pressKey(KEYPAD_1);        
  }   
  while (digitalRead(hardware_button_B)== HIGH){ //фиксируем нажатие кнопки "В" и считаем длительность, если более 2 секунд, то отправляем событие и ждем отпускания
    is_hardware_button_B_pressed = true;
    if (!is_once_button_pressed){
      if (millis()-pressTimer>LONGPRESSTIME){
        is_once_button_pressed = true;
        pressKey(KEYPAD_4);
      }
    }
  }
  if (!is_once_button_pressed && is_hardware_button_B_pressed && millis()-pressTimer<LONGPRESSTIME){ //фиксируем одиночное нажатие кнопки "B" менее LONGPRESSTIME
        is_once_button_pressed = true;
        pressKey(KEYPAD_2);  
  }     
  // It's better to use DigiKeyboard.delay() over the regular Arduino delay()
  // if doing keyboard stuff because it keeps talking to the computer to make
  // sure the computer knows the keyboard is alive and connected
  DigiKeyboard.delay(250);
}

void pressKey(int key){   
  DigiKeyboard.update();
  DigiKeyboard.sendKeyPress(key,0);
  DigiKeyboard.sendKeyPress(0,0);   
}
         
  
