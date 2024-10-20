/**/
#ifndef   DailyTimer_h
#define   DailyTimer_h
/**/
#include <Arduino.h>
/*Описываем объект класса "Суточный таймер"*/
class DailyTimer{
  /*Пин подключения релейного модуля*/
  uint8_t pinUsed;
  /*Порядковый номер объекта управления*/
  uint8_t number;
  /*Количество объектов класса*/
  static uint8_t objCount;
  /*Маркер состояния объекта управления*/
  bool marker;
  /*Текущий статус доступности управления*/
  bool isActive;
  /*Время включения - согласовываем с данными от модуля DS3231/DS1307/DS3102*/
  uint32_t timeon;
  /*Время выключения - согласовываем с данными от модуля DS3231/DS1307/DS3102*/
  uint32_t timeoff;
  /*Текущее время приведённое в формат целого числа*/
  uint32_t currtime;
public:
  /*Конструктор объекта класса, в качестве параметра номере пина подключения релейного модуля*/
  DailyTimer(uint8_t,uint32_t,uint32_t);
  /*Получить количество объектов управления*/
  uint8_t getObjectsCount(){return DailyTimer::objCount;}
  /*Получить порядковый номер объекта управления*/
  uint8_t getDeviceID(){return this->number;};
  /*Управление объектом, установка флага доступности управления*/
  void SetActivity(bool);
  /*Запрос состояния флага доступности управления*/
  bool GetActivity(){return this->isActive;};
  /*Управление объектом, получаем в строке текущее время от модуля DS1307*/
  void Control(char*);
  /**/
  uint32_t GetCurrTime(){return this->currtime;};
};
/**/
#endif
