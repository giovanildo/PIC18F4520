#include <p18f4520.h>
#include "lcd.h"

#pragma config PBADEN=OFF

void main(){
	int i, tamanho;
	char str[20] = "Ola, Mundo!";
	char str2[16] = "Tudo certo?";
	OSCCON = 0b01100010;
	ADCON1 =0x0F;
	lcd_configura();

	while(1){
		printf(str);
		deley_s();
		deley_s();
		printf(str2);
		deley_s();
		deley_s();
	}

}