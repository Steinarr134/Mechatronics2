/*
 * main.c
 *
 *  Created on: Jan 30, 2023
 *      Author: Notandi
 */


#include <steinarrdelay.h>
#include <avr/io.h>

#define LEDMASK 0x20

int main()
{
	DDRB |= LEDMASK;
	while (1)
	{
		delay_us(10);
		PORTB ^= LEDMASK;
	}

}
