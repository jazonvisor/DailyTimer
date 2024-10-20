#include "defines.h"
#include "variables.h"

/*Суточный таймер, дата испытания 11.10.2024*/
#include "DailyTimer.h"
/**/
#include "MenuList.h"
/*Используем именно эту библиотеку для получения данных о времени из модуля DS1307*/
#include <iarduino_RTC.h>
/*Подключаем библиотеку для работы с прерываниями по таймеру*/
#include <TimerOne.h>
/*Для работы с led-индикаторами на базе драйвера MAX7219*/
#include <LedControl.h>
/*Для работы с пультом IR и приёмником IR*/
#include <iarduino_IR_RX.h>

/*Работаем с модулем часов реального времени RTC DS1307, создаём объект*/
iarduino_RTC watch(RTC_DS1307);

/*Объект Display для работы с семисегментным дисплеем на базе драйвера MAX7219*/
LedControl Display=LedControl(DATAIN,CLK,LOAD,2);

/*Создаём объект листа меню*/
MenuList MenuList(sizeof(RootMenuList)/8);

/*Подключение заголовочного файла с функциями*/
#include "functions.h"

/*Создаём объекты для управления по времени*/
DailyTimer Relay1(Relay1Pin,Relay1Timeon,Relay1Timeoff);
DailyTimer Relay2(Relay2Pin,Relay2Timeon,Relay2Timeoff);

/*Объект IR для получения данных о нажатой кнопке на пульте*/
iarduino_IR_RX IR(IR_PIN);

void setup(){
  /**/
  delay(300);      
  /*Только для отладки*/                                       
  Serial.begin(9600); 
  /*Инициируем работу с модулем DS1307*/                                    
  watch.begin();
  /*Активируем управление релейными модулями*/
  Relay1.SetActivity(true);
  Relay2.SetActivity(true);
  /*Выводим левый и правый дисплеи из спящего режима*/
  Display.shutdown(LSTRING,false);
  Display.shutdown(RSTRING,false);
  /*Установка яркости левого и правого дисплеев*/
  Display.setIntensity(LSTRING,8);
  Display.setIntensity(RSTRING,8);
  /*Очистка обоих дисплеев*/
  Display.clearDisplay(LSTRING);
  Display.clearDisplay(RSTRING);
  /*Инициализация прерываний раз в полсекунды*/
  Timer1.initialize(500000);
  Timer1.attachInterrupt(TimingISR);

  /*Работаем с IR приёмником*/
  IR.begin();

  /*Задание режима вывода на дисплей*/
  MODE=SHOW_DATE_TIME;
}

void loop(){
  /*Если в буфере имеются данные, принятые с пульта (была нажата кнопка)*/
  if(IR.check()) IRRemotePressHandler(IR.data);  /*Вызываем обработчик нажатий кнопок*/                                
    
  /**/
  if(Update==ON){
    /*Обновление led-дисплеев*/
    StringsUpdate();
    /*Обновление данных о текущем времени*/
    currentTime=watch.gettime("His");
  }
  
  /*Управляем релейными модулями*/
  Relay1.Control(currentTime);
  Relay2.Control(currentTime);
}
