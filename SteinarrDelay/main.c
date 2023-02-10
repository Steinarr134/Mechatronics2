/*
 * main.c
 *
 *  Created on: Jan 30, 2023
 *      Author: Notandi
 */


#include <avr/io.h>
#include "delay_lib/steinarr_delay.h"

#define LEDON PORTB=0xFF;
#define LEDOFF PORTB=0;

int main()
{

	DDRB |= 0x20;
	unsigned char N = 255;
	while (1)
	{
//		LEDON;
//		delay_us(10);
//		LEDOFF;
//		delay_us(10);
		for(unsigned char i = 0; i<N; i++)
		{
			for(int j=0; j<50; j++)
			{
				LEDON;
				delay_us(i);
				LEDOFF;
				delay_us(255-i);
			}

		}
		for(unsigned char i = 0; i<N; i++)
		{
			for(int j=0; j<50; j++)
			{
				LEDON;
				delay_us(255-i);
				LEDOFF;
				delay_us(i);
			}
		}

	}
}
//		delay_1us();	// 16 cycles
//		PORTB = 0x20;	// 1
//		delay_1us();	// 16
//		PORTB = 0;		// 1
//	}			// loop -> 2
//					//   = 36
//}					// 36/16 Mhz = 2.25 us



//		delay_half_us(); 	// 8 cycles
//		PORTB = 0x20;		// 1 cycle
//		delay_half_us();	// 8 cycles
//		PORTB = 0;			// 1 cycle
//	}				// loop -> 2 cycles
//}					// 		== 20 cycles
