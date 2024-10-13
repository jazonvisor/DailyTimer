/*Обработчик прерывания по таймеру*/
void TimingISR();

void TimingISR(){
    Update=ON;
    ClockPoint=(~ClockPoint)&0x01;
}