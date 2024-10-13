#include <Arduino.h>
/*Время включения и выключения преобразованные в формат целых чисел*/
uint16_t Relay1Timeon=120000;
uint16_t Relay1Timeoff=220000;

/*Время включения и выключения преобразованные в формат целых чисел*/
uint16_t Relay2Timeon=193000;
uint16_t Relay2Timeoff=183000;

/*Пины подключения релейных модулей*/
const uint8_t Relay1Pin=3;
const uint8_t Relay2Pin=4;

/*Вспомогательные для TimerOne*/
unsigned char ClockPoint=1;
unsigned char Update;

/*Строки подготовки для вывода на левый и правый дисплеи*/
byte lString[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
byte rString[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

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