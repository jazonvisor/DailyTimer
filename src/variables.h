#include <Arduino.h>
/*Время включения и выключения преобразованные в формат целых чисел*/
uint16_t Relay1Timeon=120000;
uint16_t Relay1Timeoff=220000;

/*Время включения и выключения преобразованные в формат целых чисел*/
uint16_t Relay2Timeon=183000;
uint16_t Relay2Timeoff=193000;

/*Пины подключения релейных модулей*/
const uint8_t Relay1Pin=3;
const uint8_t Relay2Pin=4;