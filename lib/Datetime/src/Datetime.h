#ifndef DATETIME_h
#define DATETIME_h

#include <Arduino.h>

/*Формирование объекта - объект для работы с датой/временем - настройка, вычисление високосного года и пр.*/
class Datetime{
  /*Метод определения, является ли год високосным по версии Microsoft*/
  bool getLeapInfo(uint16_t);
  /*Метод выведения количества дней в месяце*/
  uint8_t getMaxDays(void);
  /*Текущая операция*/
  enum:uint8_t{WAIT,SET_YEAR,SET_MONTH,SET_DAY,SET_WEEKDAY,SET_HOURS,SET_MINUTES,SET_SECONDS}NOW_OP;
  /*Перечисление месяцев*/
  enum:uint8_t{JANUARY=1,FEBRUARY=2,MARCH=3,APRIL=4,MAY=5,JUNE=6,JULE=7,AUGUST=8,SEPTEMBER=9,OCTOBER=10,NOVEMBER=11,DECEMBER=12};
  /*Флаг високосного года*/
  bool YearIsLeap;
  /*Год*/
  uint8_t nowYear;
  /*Месяц*/
  uint8_t nowMonth;
  /*День*/
  uint8_t nowDay;
  /*День недели*/
  uint8_t nowWeekday;
  /*Часы*/
  uint8_t nowHours;
  /*Минуты*/
  uint8_t nowMinutes;
  /*Секунды*/
  uint8_t nowSeconds;
  /**/
  uint8_t startValue;
  /**/
  uint8_t endValue;
  /**/
  uint8_t currValue;
public:
  /*Конструктор*/
  Datetime();
  /*Сохранение значения текущего года для последующей обработки*/
  void SetYear(uint8_t);
  /**/
  uint8_t getYear(){return this->nowYear;};
  /*Установка месяца*/
  void SetMonth(uint8_t nowMonth){this->nowMonth=nowMonth;};
  /**/
  uint8_t getMonth(){return this->nowMonth;};
  /*Установка дня*/
  void SetDay(uint8_t nowDay){this->nowDay=nowDay;};
  /**/
  uint8_t getDay(){return this->nowDay;};
  /*Установка дня недели*/
  void SetWeekday(uint8_t);
  /**/
  uint8_t getWeekday(){return this->nowWeekday;};
  /*Установка часа*/
  void SetHours(uint8_t nowHours){this->nowHours=nowHours;};
  /**/
  uint8_t getHours(){return this->nowHours;};
  /*Установка минут*/
  void SetMinutes(uint8_t nowMinutes){this->nowMinutes=nowMinutes;};
  /**/
  uint8_t getMinutes(){return this->nowMinutes;};
  /*Установка секунд*/
  void SetSeconds(uint8_t nowSeconds){this->nowSeconds=nowSeconds;};
  /**/
  uint8_t getSeconds(){return this->nowSeconds;};
  /*Метод установки значения в пределах заданного диапазона*/
  void SetValue(bool);
  /**/
  uint8_t getValue(){return this->currValue;};
  /*Получить текущую операцию при изменении значения*/
  uint8_t getNowOp(){return this->NOW_OP;};
  /*Установить текущую операцию при изменении значения*/
  void setNowOp(uint8_t);
};

#endif