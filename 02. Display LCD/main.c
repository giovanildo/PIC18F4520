#include <p18f4520.h>
#pragma config PBADEN=OFF

#define LCD_DADOS PORTD

#define LCD_RS PORTDbits.RD4
#define LCD_RW PORTDbits.RD5
#define LCD_EN PORTDbits.RD6

#define TRIS_LCD_DADOS	TRISD
#define TRIS_LCD_RS 	TRISDbits.TRISD4
#define TRIS_LCD_RW 	TRISDbits.TRISD5
#define TRIS_LCD_EN 	TRISDbits.TRISD6

void envia_comando(unsigned char);
void envia_caracter(unsigned char);
void lcd_configura();
void lcd_inicializa();
void deley();
void deley15_ms();


void deley(){
	long int i;
	for(i = 0; i < 32000; i++){}
}
void deley15_ms(){
	int i;
	for(i = 0; i < 900; i++){}

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

	LCD_DADOS &= 0xf0;
	LCD_DADOS |= (comando & 0x0f);

	LCD_EN = 0b1;
	deley15_ms();
	LCD_EN = 0b0;

}

/*
 * Inicializa LCD
 */
void lcd_inicializa()
{ 
	LCD_DADOS = 0b0000;
	LCD_RS = 0; 
	LCD_RW = 0;
	LCD_EN = 0;	
	envia_comando(0b0011);
	envia_comando(0b0011);
	envia_comando(0b0011);
	envia_comando(0b0010);
	envia_comando(0b0010);
	envia_comando(0b0001);
	envia_comando(0b0000);
	envia_comando(0b1111);

	
}

void envia_caracter(unsigned char caracter){
	LCD_RS = 0b1; 
	LCD_RW = 0b0;
	LCD_EN = 0b0;

}

void main(){
	lcd_configura();
	lcd_inicializa();
	
	OSCCON=0b01100010;
	ADCON1=0x0F;
	
	while(1){
	
	}


}