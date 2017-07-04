#include <p18f4520.h>
#include "lcd.h"

#pragma config PBADEN=OFF

void main(){
	int i, tamanho;
	char str[20] = "Ola, Mundo!";
	char str2[16] = "Tudo certo?";
	OSCCON = 0b01100010;
	ADCON1 =0x0F;

	while(1){

		lcd_configura();
		lcd_inicializa();
		printf(str);

		deley_s();
		lcd_configura();
		lcd_inicializa();
		printf(str2);
	
	}

}