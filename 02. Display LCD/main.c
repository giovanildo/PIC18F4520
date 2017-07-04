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
void deley_s();
void deley15_ms();
void pulse_enable();
int contar(char *);
void printf(char *); 



void deley_s(){
	unsigned long int i;
	for(i = 0; i < 32000; i++){}
}

void deley15_ms(){
	unsigned long int i;
	for(i = 0; i < 3200; i++){}

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
	LCD_DADOS = 0b0000;
	LCD_RS = 0; 
	LCD_RW = 0;
	LCD_EN = 0;	
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

void printf(char *str){
	int tamanho, i;
	tamanho = contar(str);
	for(i = 0; i < tamanho; i++){
		envia_caracter(str[i]);

	}
}

void main(){
	int i, tamanho;
	char str[20] = "Maria Victoria !";
	char str2[16] = "de Sousa Mareano ";
	char str3[16] = " EST, a Lindona das Tapiocas";

	OSCCON = 0b01100010;
	ADCON1 =0x0F;
	TRISBbits.TRISB0 = 0;	
	
	PORTBbits.RB0 = 0;
	deley15_ms(); 
	PORTBbits.RB0 = 1; 	
	deley15_ms(); 
	PORTBbits.RB0 = 0;
	deley_s(); 
	PORTBbits.RB0 = 1; 	
	deley_s(); 



	while(1){

	
		lcd_configura();
		lcd_inicializa();
		printf(str);
		
	
		deley_s();
		lcd_configura();
		lcd_inicializa();
		printf(str2);
	
		deley_s();
		lcd_configura();
		lcd_inicializa();
		printf(str3);
	

		PORTBbits.RB0 = 0;
		deley_s(); 
		PORTBbits.RB0 = 1; 	
		deley_s(); 
	}

}