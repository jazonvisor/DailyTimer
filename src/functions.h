/*Обработчик прерывания по таймеру*/
void TimingISR();
/*Формирование строк - левая и правая*/
void StringsUpdate();
/*Форматирование даты/времени*/
void ShowDateTime();
/*Показываем настройку даты*/
void ShowSetDate();
/*Отрисовка корневого листа меню*/
void ShowMenuSDTList();
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
      ShowMenuSDTList();
      break;
    /*Показываем настройку значений даты*/
    case SET_DATE:
      ShowSetDate();
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

/*Показываем настройку даты*/
void ShowSetDate(){
  /*Формируем левую часть*/
  for(int i=0;i<8;i++){
    lString[i]=RootMenuList[MenuList.getListItem()][i];
  }
  /*Формируем правую часть*/
  rString[0]=symbol[2];
  rString[1]=symbol[0];
  /*Смотрим текущую операцию настройки*/
  enum:uint8_t{WAIT,SET_YEAR,SET_MONTH,SET_DAY};
  switch(Datetime.getNowOp()){
    case WAIT:
      rString[2]=symbol[Datetime.getYear()/10];
      rString[3]=symbol[Datetime.getYear()%10]^point;
      rString[4]=symbol[Datetime.getMonth()/10];
      rString[5]=symbol[Datetime.getMonth()%10]^point;
      rString[6]=symbol[Datetime.getDay()/10];
      rString[7]=symbol[Datetime.getDay()%10];
      break;
    case SET_YEAR:
      if(ClockPoint){
        rString[2]=symbol[Datetime.getYear()/10];
        rString[3]=symbol[Datetime.getYear()%10]^point;
      }
      else{
        rString[2]=empty;
        rString[3]=empty^point;
      }
      rString[4]=symbol[Datetime.getMonth()/10];
      rString[5]=symbol[Datetime.getMonth()%10]^point;
      rString[6]=symbol[Datetime.getDay()/10];
      rString[7]=symbol[Datetime.getDay()%10];
      break;
    case SET_MONTH:
      rString[2]=symbol[Datetime.getYear()/10];
      rString[3]=symbol[Datetime.getYear()%10]^point;
      if(ClockPoint){
        rString[4]=symbol[Datetime.getMonth()/10];
        rString[5]=symbol[Datetime.getMonth()%10]^point;
      }
      else{
        rString[4]=empty;
        rString[5]=empty^point;
      }
      rString[6]=symbol[Datetime.getDay()/10];
      rString[7]=symbol[Datetime.getDay()%10];
      break;
    case SET_DAY:
      rString[2]=symbol[Datetime.getYear()/10];
      rString[3]=symbol[Datetime.getYear()%10]^point;
      rString[4]=symbol[Datetime.getMonth()/10];
      rString[5]=symbol[Datetime.getMonth()%10]^point;
      if(ClockPoint){
        rString[6]=symbol[Datetime.getDay()/10];
        rString[7]=symbol[Datetime.getDay()%10];
      }
      else{
        rString[6]=empty;
        rString[7]=empty;
      }
      break; 
  }
}

/*Отрисовка корневого листа меню*/
void ShowMenuSDTList(){
  /*Левая часть*/
  byte menuString[]={0x66,0x72,0x4F,0x76,0x3E,0x0,0x0,0x0};
  for(int i=0;i<8;i++){
    lString[i]=menuString[i];
  }
  /*Формируем правую часть*/
  for(int i=0;i<8;i++){
    rString[i]=RootMenuList[MenuList.getListItem()][i];
  }
}

void TimingISR(){
    Update=ON;
    ClockPoint=(~ClockPoint)&0x01;
}