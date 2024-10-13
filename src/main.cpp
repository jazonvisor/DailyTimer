#include "defines.h"
#include "variables.h"
/*Суточный таймер, дата испытания 11.10.2024*/
#include "DailyTimer.h"
/*Используем именно эту библиотеку для получения данных о времени из модуля DS1307*/
#include <iarduino_RTC.h>

/*Работаем с модулем часов реального времени RTC DS1307, создаём объект*/
iarduino_RTC watch(RTC_DS1307);

/*Создаём объекты для управления по времени*/
DailyTimer Relay1(Relay1Pin,Relay1Timeon,Relay1Timeoff);
DailyTimer Relay2(Relay2Pin,Relay2Timeon,Relay2Timeoff);

void setup(){
  /**/
  delay(300);      
  /*Только для отладки*/                                       
  //Serial.begin(9600); 
  /*Инициируем работу с модулем DS1307*/                                    
  watch.begin();
  /*Активируем управление релейными модулями*/
  Relay1.SetActivity(true);
  Relay2.SetActivity(true);
}

void loop(){
  /**/
  char* currentTime=watch.gettime("His");
  /*Управляем релейными модулями*/
  Relay1.Control(currentTime);
  Relay2.Control(currentTime);
}