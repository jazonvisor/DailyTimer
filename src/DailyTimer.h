/*Суточный таймер, дата испытания 11.10.2024*/
/*Обязательно подключаем эту библиотеку*/
//#include <Arduino.h>

/*Описываем класс*/
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



