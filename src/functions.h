/*Обработчик прерывания по таймеру*/
void TimingISR();
/*Формирование строк - левая и правая*/
void StringsUpdate();
/*Форматирование даты/времени*/
void ShowDateTime();
/*Функция вывода на дисплей*/
void ToDisplay();
/*Обработчик нажатия кнопок IR-пульта*/
void IRRemotePressHandler(uint16_t);
/*Обработчик нажатия кнопки Menu*/
void ButtonMenuPressHandler();

/*Обработчик нажатия кнопок IR-пульта*/
void IRRemotePressHandler(uint16_t keycode){
  switch(keycode){
    case KEY_MENU:
      ButtonMenuPressHandler();
      break;
    case KEY_EXIT:
      //ButtonExitPressHandler();
      break;
    case KEY_OK:
      //ButtonOkPressHandler();
      break;
    case KEY_CHUP:
      //ButtonUpPressHandler();
      break;
    case KEY_CHDN:
      //ButtonDownPressHandler();
      break;
    case KEY_RIGTH:
      //ButtonRigthPressHandler();
      break;
    case KEY_LEFT:
      //ButtonLeftPressHandler();
      break;
  }
}

/*Обработчик нажатия кнопки Menu*/
void ButtonMenuPressHandler(){
  if(MODE==SHOW_DATE_TIME){
    /*Переход в режим показа листа меню настройки даты/времени*/
    MODE=MENU_SDT_LIST;
  }
}

/*Функция вывода на дисплей*/
void ToDisplay(){
  for(int j=0;j<8;j++){
    /*Выводим левую часть*/
    Display.setRow(LSTRING,j,lString[j]);
    /*Выводим правую часть*/
    Display.setRow(RSTRING,j,rString[j]);
  }
}

/*Формирование строк - левая и правая*/
void StringsUpdate(){
  /*Проверяем режимы*/
  switch(MODE)
  {
    /*Показываем дату и время*/
    case SHOW_DATE_TIME:
      ShowDateTime();
      Update = OFF;
      break;
    /*Показываем/скроллим лист меню*/
    case MENU_SDT_LIST:
      //ShowMenuSDTList();
      break;
    /*Показываем настройку значений даты*/
    case SET_DATE:
      //ShowSetDate();
      Update = OFF;
      break;
    /*Показываем настройку значений времени*/
    case SET_TIME:
      //ShowSetTime();
      Update = OFF;
      break;
    /*Показ анимации сохранения*/
    case SAVING:
      //ShowSavingAnimation();
      break;
  }
  ToDisplay();
  //Update = OFF;
}

/*Форматирование даты/времени*/
void ShowDateTime(){
  /*Получение данных о текущем времени в виде параметров*/
  watch.gettime();
  /*Формируем левую часть*/
  lString[0]=symbol[2];
  lString[1]=symbol[0];
  lString[2]=symbol[watch.year/10];
  lString[3]=symbol[watch.year%10]^point;
  lString[4]=symbol[watch.month/10];
  lString[5]=symbol[watch.month%10]^point;
  lString[6]=symbol[watch.day/10];
  lString[7]=symbol[watch.day%10];
  /*Формируем правую часть*/
  rString[0]=empty;
  rString[1]=empty;
  rString[2]=symbol[watch.Hours/10];
  if(ClockPoint)
    rString[3]=symbol[watch.Hours%10];
  else
    rString[3]=symbol[watch.Hours%10]^point;
  rString[4]=symbol[watch.minutes/10];
  if(ClockPoint)
    rString[5]=symbol[watch.minutes%10];
  else
    rString[5]=symbol[watch.minutes%10]^point;
  rString[6]=symbol[watch.seconds/10];
  rString[7]=symbol[watch.seconds%10];
}

void TimingISR(){
    Update=ON;
    ClockPoint=(~ClockPoint)&0x01;
}