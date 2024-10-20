/*Подключаем заголовочный файл с описанием объекта класса*/
#include "DailyTimer.h"

/*Статический счетчик количества объектов управления*/
uint8_t DailyTimer::objCount=0;

/*Конструктор*/
DailyTimer::DailyTimer(uint8_t pinUsed,uint32_t timeon,uint32_t timeoff){
  /*Привязываемся к указанному пину, назначаем режим работы*/
  pinMode(pinUsed,OUTPUT);
  /**/
  this->pinUsed=pinUsed;
  /*Для сохрания промежуточного состояния объекта управления*/
  marker=false;
  /*Флаг доступности управления*/
  isActive=false;
  /*Статическая переменная для сохранения количества объектов*/
  objCount++;
  /*Назначаем уникальный номер для объекта управления*/
  number=objCount;
  /*Основные уставки - время включения и выключения*/
  this->timeon=timeon;
  this->timeoff=timeoff;
}

/*Управление объектом, установка флага доступности управления*/
void DailyTimer::SetActivity(bool enable){
  /*Первым делом проверям временные уставки, если числа равны то сбросить флаг доступности управления*/
  /*простыми словами - при равных уставках времени включения/выключения невозможно корректно управлять*/
  /*объектом. Но если уставки различаются, флаг доступности управления должен быть установлен.*/
  (timeon==timeoff)?
    isActive=false:
      enable?isActive=true:isActive=false;
}

/*Управление объектом*/
void DailyTimer::Control(char* value){
  /*Если управление объектом доступно*/
  if(isActive){
    /*Полученную из аргумента строку преобразуем в целое число*/
    currtime=atol(value);
    /**/
    if(timeon<timeoff){
      /**/
      if(currtime>=timeon && currtime<timeoff)
        marker=true;
      else
        marker=false;
    }else{
      if(timeon>timeoff){
        if(currtime>=timeoff && currtime<timeon)
          marker=false;
        else
          marker=true;
      }
    }/*Иначе, не управлять объектом никак.*/
  }else{marker=false;};
  /*Записываем состояние маркера назначенному пину*/
  digitalWrite(pinUsed,marker);
}