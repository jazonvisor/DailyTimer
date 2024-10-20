#include <Arduino.h>
/*Время включения и выключения преобразованные в формат целых чисел*/
uint32_t Relay1Timeon=120000;
uint32_t Relay1Timeoff=220000;

/*Время включения и выключения преобразованные в формат целых чисел*/
uint32_t Relay2Timeon=193000;
uint32_t Relay2Timeoff=183000;

/*Пины подключения релейных модулей*/
const uint8_t Relay1Pin=3;
const uint8_t Relay2Pin=4;

/*Вспомогательные для TimerOne*/
unsigned char ClockPoint=1;
unsigned char Update;

/*Строки для листов меню*/
byte RootMenuList[4][8]={
                                  {0x5B,0x4F,0xF,0x0,0x3D,0x77,0xF,0x4F},/*SET DATE*/
                                  {0x5B,0x4F,0xF,0x0,0xF,0x30,0x76,0x4F},/*SET TIME*/
                                  {0x5,0x4F,0xE,0x77,0x3B,0x5B,0x4F,0xF},/*RELAYSET*/
                                  {0xFE,0x1C,0x10,0xF,0x0,0x0,0x0,0x0}};/*QUIT*/

/*Строки подготовки для вывода на левый и правый дисплеи*/
byte lString[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
byte rString[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

/*Счетчик для анимации*/
int a=0;
/*Структура временного размещения данных для настройки даты/времени*/
struct{
  uint8_t nowYear;
  uint8_t nowMonth;
  uint8_t nowDay;
  uint8_t nowHours;
  uint8_t nowMinutes;
  uint8_t nowSeconds;
} nowDateTime;

/*Режимы*/
enum MODES:uint8_t{SHOW_DATE_TIME,MENU_SDT_LIST,SET_DATE,SET_TIME,MENU_SR_LIST,SAVING}MODE;

/*Сгенерированные символы для MAX7219*/
byte symbol[]={
                    0x7E,   /*0*/
                    0x30,   /*1*/
                    0x6D,   /*2*/
                    0x79,   /*3*/
                    0x33,   /*4*/
                    0x5B,   /*5*/
                    0x5F,   /*6*/
                    0x70,   /*7*/
                    0x7F,   /*8*/
                    0x7B,   /*9*/
                    0x77,   /*A*/
                    0x1F,   /*B*/
                    0x4E,   /*C*/
                    0x3D,   /*d*/
                    0x4F,   /*E*/
                    0x47,   /*F*/
};
byte point=0x80;
byte degree=0x63;
byte sign=0x1;
byte empty=0x0;

/**/
char* currentTime;