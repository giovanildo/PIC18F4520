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
void pulse_enable();
int contar(char *);
void printf(char *);


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

	pulse_enable();

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

void pulse_enable(){
	LCD_EN = 0b1;
	deley15_ms();
	LCD_EN = 0b0;
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
	int max = 16;
	int i;
	for(i = 0; i < max; i++){
		if(str[i] == '\0'){
			return i;
		}
	}
	return i;
}

void printf(char *str){
	int tamanho, i;
	tamanho = contar(str);
	for(i = 0; i < tamanho; i++){
		envia_caracter(str[i]);

	}
}

void main(){
	int i, tamanho;
	char str[16] = "Ola, Sena";
	TRISB = 0b00000000;
	ADCON1=0x0F;
	
	lcd_configura();
	lcd_inicializa();
	
	printf(str);

	
	while(1){
		PORTB = 0b00000000;
		deley();
		PORTB = 0b11111111;
		deley();
	}


}