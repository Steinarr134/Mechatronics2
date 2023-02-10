/*
 * steinarrdelay.c
 *
 *  Created on: Jan 30, 2023
 *      Author: Notandi
 */



void delay_us(int us)
{
//	for (char i=0; i<us; i++)
//	{
//		asm("nop");
//	}
	char i = 0;
	char a = us&0xFF;
	while (i < a)
	{
		asm("nop");
		i++;
	}
}
//void delay_ms(int ms)
//{
//
//}
//void delay_s(int s)
//{
//
//}

