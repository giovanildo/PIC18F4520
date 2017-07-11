#include <p18f4520.h>
#include <stdio.h>
#include <usart.h>
#include <stdlib.h>
#include <capture.h>
#include <timers.h>
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


void deley_test(){
	long int i;
	for(i = 0; i < 32000; i++){}

}

void configura_entrada(){
	OpenCapture1( C1_EVERY_4_RISE_EDGE &
 	CAPTURE_INT_OFF );
 
	OpenTimer3( TIMER_INT_OFF &
	T3_SOURCE_INT );

}
void configura_saida(){
	OpenUSART( USART_TX_INT_OFF &
	USART_RX_INT_ON &
	USART_ASYNCH_MODE &
	USART_EIGHT_BIT &
	USART_CONT_RX,
	25);
	stdout = _H_USART;
}



void configura_interrupcao(){

	OpenCapture1( C1_EVERY_4_RISE_EDGE &
 	CAPTURE_INT_OFF );

	OpenTimer3( TIMER_INT_OFF &
	T3_SOURCE_INT );
	
	IPR1bits.RCIP = 1;
	RCONbits.IPEN = 1;
	INTCONbits.GIEH = 1;
	INTCONbits.GIEL = 1;
}

void main(){
	int x; 
	char str[16] = "Usart: ";
	OSCCON=0b01100010;
	ADCON1=0x0F;
	TRISB = 0b11111110;
	lcd_configura();
	configura_interrupcao();

	configura_saida();
	lcd_inicializa();

	printf("Ola mundo!");
	printj(str);
	while(1){
		PORTB = 0b00000000;
		deley_test();
		PORTB = 0b00000001;
		deley_test();

	}


}