/**/
#include "Datetime.h"

/*Конструктор*/
Datetime::Datetime(){
  /**/
  this->YearIsLeap=false;
  /**/
  this->NOW_OP=WAIT;
}

/**/
void Datetime::setNowOp(uint8_t NOW_OP){
  /**/
  switch(NOW_OP){
    case WAIT:
      this->NOW_OP=NOW_OP;
    break;
    case SET_YEAR:
      this->NOW_OP=NOW_OP;
      /*Определяем диапазон установки значения - от и до*/
      startValue=0;
      endValue=99;
      currValue=nowYear;
      break;
    case SET_MONTH:
      this->NOW_OP=NOW_OP;
      /*Определяем диапазон установки значения - от и до*/
      startValue=1;
      endValue=12;
      currValue=nowMonth;
      break;
    case SET_DAY:
      this->NOW_OP=NOW_OP;
      /*Определяем диапазон установки значения - от и до*/
      startValue=1;
      endValue=getMaxDays();
      currValue=nowDay;
      break;
    case SET_WEEKDAY:
      this->NOW_OP=NOW_OP;
      /*Определяем диапазон установки значения - от и до*/
      startValue=0;
      endValue=6;
      break;
    case SET_HOURS:
      this->NOW_OP=NOW_OP;
      /*Определяем диапазон установки значения - от и до*/
      startValue=0;
      endValue=23;
      currValue=nowHours;
      break;
    case SET_MINUTES:
      this->NOW_OP=NOW_OP;
      /*Определяем диапазон установки значения - от и до*/
      startValue=0;
      endValue=59;
      currValue=nowMinutes;
      break;
    case SET_SECONDS:
      this->NOW_OP=NOW_OP;
      /*Определяем диапазон установки значения - от и до*/
      startValue=0;
      endValue=59;
      currValue=nowSeconds;
      break;
  }
}

/*Метод сохранения значения текущего дня, для последующей обработки*/
void Datetime::SetWeekday(uint8_t weekday){
  this->nowWeekday=weekday;
}

/*Метод выведения количества дней в месяце*/
uint8_t Datetime::getMaxDays(void){
    uint8_t maxDay;
    switch(this->nowMonth){
      case JANUARY:
      case MARCH:
      case MAY:
      case JULE:
      case AUGUST:
      case OCTOBER:
      case DECEMBER:
        maxDay=31;
        break;
      case APRIL:
      case JUNE:
      case SEPTEMBER:
      case NOVEMBER:
        maxDay=30;
      case FEBRUARY:
        if(YearIsLeap)
          maxDay=29;
        else
          maxDay=28;
        break;
    }
    return maxDay;
}

/*Метод сохранения значения текущего года, для последующей обработки*/
void Datetime::SetYear(uint8_t nowYear){
  this->nowYear=nowYear;
  /*Получаем флаг високосного года, если указанное значение соответствует*/
  YearIsLeap=getLeapInfo(nowYear);
}
/*Метод установки значения в пределах заданного диапазона*/
void Datetime::SetValue(bool Direction){
  if(!Direction){
    if(currValue==endValue)
      currValue=startValue;
    else
      currValue++;
  }
  else{
    if(currValue==startValue)
      currValue=endValue;
    else{
      if(currValue>startValue)
        currValue--;
    }
  }
  /*Присвоение значений*/
  switch(NOW_OP){
    case SET_YEAR:
      nowYear=currValue;
      break;
    case SET_MONTH:
      nowMonth=currValue;
      break;
    case SET_DAY:
      nowDay=currValue;
      break;
    case SET_WEEKDAY:
      nowWeekday=currValue;
      break;
    case SET_HOURS:
      nowHours=currValue;
      break;
    case SET_MINUTES:
      nowMinutes=currValue;
      break;
    case SET_SECONDS:
      nowSeconds=currValue;
      break;
  }
}
/*Метод определения, является ли год високосным по версии Microsoft*/
bool Datetime::getLeapInfo(uint16_t Year){
  /*Возвращаемый результат*/
  bool checked;
  /*Заведомо известно что это не високосные годы*/
  if((Year==1700)||(Year==1800)||(Year==1900)||(Year==2100)||(Year==2200)||(Year==2300)||(Year==2500)||(Year==2600))
    checked=false;
  /*Далее нужно организовать поиск более точно, в значение*/
  /*могут попасть 1600, 2000, 2400, это високосные года*/
  else{
    if((Year==1600)||(Year==2000)||(Year==2400))
      checked = true;
    else{
      /*В итоге високосным годом будет любое оставшееся значение делящееся без остатка на 4*/
      if(Year % 4 != 0)
        checked = false;
      else
        checked = true;
    }
  }
  return checked;
}