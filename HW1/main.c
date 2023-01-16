/*
 * main.c
 *
 *  Created on: Jan 12, 2023
 *      Author: Notandi
 */

#include <avr/io.h>
int main(){
	DDRB = 0x20;
	while (1)
	{
		PORTB = 1<<5 ;
		PORTB = 0;
	}
}
