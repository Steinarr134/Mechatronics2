/*
 * main.c
 *
 *  Created on: 7 Feb 2023
 *      Author: Notandi
 */

#include <avr/io.h>
#include "HackySerial.h"


int main()
{
	USART_INIT;
	while (1)
	{
		// blocking read
		char incoming = USART_Receive();

		// retransmit the character plus one
		USART_TRANSMIT(incoming +1);
		PRINTLN;
	}
}
