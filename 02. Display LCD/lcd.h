#ifndef LCD_H
#define LCD_H


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

#endif