#include <p18f4520.h>
#include <capture.h>
#include <timers.h>
#include <usart.h>
#include <stdlib.h>
#include "lcd.h"

#pragma config OSC = INTIO67
#pragma config PBADEN=OFF


#pragma interrupt ISR_alta_prioridade
void ISR_alta_prioridade(void){
	unsigned char c;
	c = getcUSART();
	envia_caracter(c);

}


#pragma code int_alta = 0x08
void int_alta(void){
	_asm GOTO ISR_alta_prioridade _endasm
}
#pragma code

void configuraUsart(){


}

void main(){
	int i, tamanho;
	char str[20] = "Ola, Mundo!";
	char str2[16] = "";
	OSCCON = 0b01100010;
	ADCON1 =0x0F;
	TRISC = 0b10111111;

	lcd_configura();
	
	OpenCapture1( C1_EVERY_4_RISE_EDGE &
 	CAPTURE_INT_OFF );
 

	OpenTimer3( TIMER_INT_OFF &
	T3_SOURCE_INT );

	OpenUSART( USART_TX_INT_OFF &
	USART_RX_INT_ON &
	USART_ASYNCH_MODE &
	USART_EIGHT_BIT &
	USART_CONT_RX,
	25);
	
	
	IPR1bits.RCIP = 1;
	RCONbits.IPEN = 1;
	INTCONbits.GIEH = 1;
	INTCONbits.GIEL = 1;
	
	deley_s();
	printj(str);
	deley_s();	
	lcd_inicializa();

	putcUSART('c');
	while(1){
		printj(str2);
		deley_s();	
		deley_s();	
		deley_s();	
		deley_s();	
		deley_s();	
		deley_s();	
		printj(str2);

	}

}