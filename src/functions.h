/*Обработчик прерывания по таймеру*/
void TimingISR();
/**/
void StringsUpdate();
/**/
void ToDisplay();

void ToDisplay(){
  for(int j=0;j<8;j++){
    /*Выводим левую часть*/
    Display.setRow(LSTRING,j,lString[j]);
    /*Выводим правую часть*/
    Display.setRow(RSTRING,j,rString[j]);
  }
}

void StringsUpdate(){
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
  ToDisplay();
  Update = OFF;
}

void TimingISR(){
    Update=ON;
    ClockPoint=(~ClockPoint)&0x01;
}