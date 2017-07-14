#include <p18f4520.h>
#include "lcd.h"

void deley_s(){
	unsigned long int i;
	for(i = 0; i < 40000; i++){}
}

void deley15_ms(){
	unsigned long int i;
	for(i = 0; i < 100; i++){}

}
/*
 * Configura as portas como saída. 
 */
void lcd_configura(){
	TRIS_LCD_DADOS = 0b0000;
	TRIS_LCD_RS = 0;	
	TRIS_LCD_RW = 0;	
	TRIS_LCD_EN = 0;
}


void envia_comando(unsigned char comando){
	LCD_RS = 0b0; 
	LCD_RW = 0b0;
	LCD_EN = 0b0;
	LCD_DADOS = comando;
	pulse_enable();

}

/*
 * Inicializa LCD
 */
void lcd_inicializa()
{ 
	envia_comando(0b0011);
	envia_comando(0b0011);
	envia_comando(0b0011);
	envia_comando(0b0010);
	envia_comando(0b0010);
	envia_comando(0b1000);
	envia_comando(0b0000);
	envia_comando(0b1111);
	envia_comando(0b0000);
	envia_comando(0b0110);
	envia_comando(0b0000);
	envia_comando(0b0001);
}

void pulse_enable(){
	LCD_EN = 0b1;
	LCD_EN = 0b0;
	deley15_ms();
}
void envia_caracter(unsigned char caracter){
	LCD_RS = 0b1; 
	LCD_RW = 0b0;
	LCD_EN = 0b0;

	LCD_DADOS &= 0xf0;
	LCD_DADOS |= (caracter >> 4);
	pulse_enable();

	LCD_DADOS &= 0xf0;
	LCD_DADOS |= (caracter & 0x0f);
	pulse_enable();

}
int contar(char *str){
	int max = 20;
	int i;
	for(i = 0; i < max; i++){
		if(str[i] == '\0'){
			return i;
		}
	}
	return i;
}

void printj(char *str){
	int tamanho, i;
	lcd_inicializa();
	tamanho = contar(str);
	for(i = 0; i < tamanho; i++){
		envia_caracter(str[i]);

	}
}
