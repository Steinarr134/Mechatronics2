
#include <avr/io.h>

#define LEDMASK 0x20

void LedInit(){
	DDRB |= LEDMASK;
}
void LedOn(){
	PORTB|=LEDMASK;
}
void LedOff(){
	PORTB&=(!LEDMASK);
}
void LedToggle(){
	PORTB^=LEDMASK;
}
