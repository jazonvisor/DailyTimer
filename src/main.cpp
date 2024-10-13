/*Суточный таймер, дата испытания 11.10.2024*/
#include "DailyTimer.h"
/*Используем именно эту библиотеку для получения данных о времени из модуля DS1307*/
#include <iarduino_RTC.h>

/*Пин подключения релейного модуля*/
const uint8_t relayPin=3;
/*Время включения и выключения преобразованные в формат целых чисел*/
uint16_t timeon=160030;
uint16_t timeoff=160300;

/*Работаем с модулем часов реального времени RTC DS1307, создаём объект*/
iarduino_RTC watch(RTC_DS1307);

/*Создаём объект для управления по времени*/
DailyTimer Relay1(relayPin,timeon,timeoff);

void setup(){
  /**/
  delay(300);      
  /*Только для отладки*/                                       
  Serial.begin(9600); 
  /*Инициируем работу с модулем DS1307*/                                    
  watch.begin();
  /*Активируем управление модулем*/
  Relay1.SetActivity(true);
}

void loop(){
  /*Управляем релейным модулем*/
  Relay1.Control(watch.gettime("His"));
}
