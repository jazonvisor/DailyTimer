/**/
#ifndef   MenuList_h
#define   MenuList_h
#include "Arduino.h"
/*Описываем объект - лист меню*/
class MenuList{
  /*Текущий пункт листа меню*/
  uint8_t listItem;
  /*Размерность листа меню*/
  uint8_t listSize;
public:
  /*Конструктор*/
  MenuList(uint8_t);
  /*Получить текущий пункт листа меню*/
  uint8_t getListItem();
  /*Проход по пунктам листа меню*/
  void ChangeListItem(bool);
  /*Сброс значений листа меню*/
  void resetMenuList();
};
/**/
#endif