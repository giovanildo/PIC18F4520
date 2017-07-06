#include <p18f4520.h>
#include <capture.h>
#include <timers.h>
#include <usart.h>
#include <stdlib.h>
#include "lcd.h"

#pragma config PBADEN=OFF

#pragma interrupt ISR_alta_prioridade
void ISR_alta_prioridade(void){
	char str[16] = "Teste2";
	str[0] = getcUSART();
	
	printj(str);
}


#pragma code int_alta = 0x08
void int_alta(void){
	_asm GOTO ISR_alta_prioridade _endasm
}
#pragma code





void main(){
	int i, tamanho;
	char str[20] = "Ola, Mundo!";
	char str2[16] = "Tudo certo?";
	OSCCON = 0b01100010;
	ADCON1 =0x0F;
	TRISC = 0b10111111;

	lcd_configura();
	printj("Teste");
	
    // Configure Capture1
	OpenCapture1( C1_EVERY_4_RISE_EDGE &
 	CAPTURE_INT_OFF );
 // Configure Timer3
	OpenTimer3( TIMER_INT_OFF &
	T3_SOURCE_INT );

	OpenUSART( USART_TX_INT_OFF &
	USART_RX_INT_ON &
	USART_ASYNCH_MODE &
	USART_EIGHT_BIT &
	USART_CONT_RX,
	129 );
	
	baudUSART(BAUD_8_BIT_RATE
	&BAUD_AUTO_OFF
	&BAUD_WAKEUP_OFF);
	
	IPR1bits.RCIP = 1;
	RCONbits.IPEN = 1;
	INTCONbits.GIEH = 1;
	INTCONbits.GIEL = 1;


		

	while(1){
		printj(str);
		deley_s();
		deley_s();
		printj(str2);
		deley_s();
		deley_s();
	}

}