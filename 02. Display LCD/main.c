#include <p18f4520.h>
#include "lcd.h"


#pragma config OSC = INTIO67
#pragma config PBADEN=OFF

void main(){
	int i, tamanho;
	char str[20] = "Ola, Mundo!";
	char str2[16] = "Tudo certo?";
	OSCCON = 0b01100010;
	ADCON1 =0x0F;
	lcd_configura();

	while(1){
		printj(str);
		deley_s();
		deley_s();
		printj(str2);
		deley_s();
		deley_s();
	}

}