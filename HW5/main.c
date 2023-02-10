
#include "HackySerial.h"
#include "steinarr_delay.h"
int main()
{
	// initialize USART
	USART_INIT;
	// set LED pin direction
	DDRB = 0x20;
	// set pin direction (pin D6 on arduino nano)
	DDRD |= (1<<PD6);
	// configure timer 1 as Fast PWM mode using OCR0A,
	// it will create a PWM on pin D6 (the OCR0A pin)
	TCCR0A |= (1<<COM0A1) | (1<<WGM01) | (1<<WGM00);
	TCCR0B |= (1<<CS00);	//No-Prescalar

	while(1)
	{
		// read incoming byte
		char incoming = USART_Receive();
		// only react if it's a number
		if (('0' <= incoming) && (incoming <= '9'))
		{
			USART_TRANSMIT(incoming); // echo for debugging
			PORTB ^= 0x20; // blink the LED for fun

			// scale the number up from 0-9 to 0-256
			// and put the result into
			OCR0A = (incoming-'0')*28; // note 28*9 = 252
		}
	}
}
