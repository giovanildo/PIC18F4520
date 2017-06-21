#include <p18f4520.h>

void deley_segundos(){
	long int i;
	for(i = 0; i < 50000;i++){}
}

void main(){
	TRISB = 0b11111110;
	PORTB = 0b11111110;
	while(1){
		PORTB = 0b11111111;
		deley_segundos();
		PORTB = 0b11111110;
		deley_segundos();
	}
}
