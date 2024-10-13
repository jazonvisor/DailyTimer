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