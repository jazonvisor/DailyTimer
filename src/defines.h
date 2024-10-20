/*Вспомогательные для TimerOne*/
#define ON  1
#define OFF 0

/*Пины подключения дисплея на базе MAX7219*/
#define DATAIN    5
#define CLK       6
#define LOAD      7

/*Вспомогательные для объекта Display*/
#define RSTRING   0
#define LSTRING   1

/*Пин подключения IR приёмника*/
#define IR_PIN    2

/*Коды кнопок используемого пульта*/
#define KEY_0     0x807FC837
#define KEY_1     0x807F00FF
#define KEY_CHUP  0x807FE817
#define KEY_CHDN  0x807F58A7
#define KEY_LEFT  0x807FB04F
#define KEY_RIGTH 0x807F28D7
#define KEY_PGINC 0x807F8877
#define KEY_PGDEC 0x807FA05F
#define KEY_MENU  0x807F30CF
#define KEY_EXIT  0x807FA857
#define KEY_OK    0x807FF807