/*Реализация методов и полей класса MenuList*/
#include "MenuList.h"
/*Конструктор*/
MenuList::MenuList(uint8_t ls){
  /*Всегда начинать с первого пункта меню в листе*/
  listItem=0;
  /*Вычислить размерность листа меню*/
  listSize=ls-1;
}
/*Получить текущий пункт листа меню*/
uint8_t MenuList::getListItem(){return this->listItem;}
/*Проход по пунктам листа меню*/
void MenuList::ChangeListItem(bool Direction){
  if(Direction){
    if(listItem>=listSize)
      listItem=listSize;
    else
      listItem++;
  }
  else{
    if(listItem<=0)
      listItem=0;
    else
      listItem--;
  }
}
/*Сброс значений листа меню*/
void MenuList::resetMenuList(){
  listItem=0;
}