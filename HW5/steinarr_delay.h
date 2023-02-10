/*
 * steinarr_delay.h
 *
 *  Created on: Jan 30, 2023
 *      Author: Notandi
 */

#ifndef DELAY_LIB_STEINARR_DELAY_H_
#define DELAY_LIB_STEINARR_DELAY_H_

void delay_us(unsigned int us);
void delay_ms(unsigned int ms);
void delay_s(unsigned int s);
void d_test(unsigned char us);

void delay_half_us();
void delay_1us();

#endif // DELAY_LIB_STEINARR_DELAY_H_

// Macro that delays for 9+4*us cycles
// push+push+ldi+ldi+pop+pop = 2+2+1+1+2+2 = 10 cycles
// loop is sbiw+brne = 2+2 = 4 cycles except the last one
// which is only 3, bringing the total to 9+4*us
#define DELAY_9P4(i) \
do { \
	asm volatile ("push r24"::);\
	asm volatile ("push r25"::);\
	asm volatile("ldi r25, %0"::"M"(i>>8));\
	asm volatile("ldi r24, %0"::"M"(i&0xff));\
	asm volatile("sbiw r24, 0x01");\
	asm volatile("brne .-4");\
	asm volatile ("pop r25"::);\
	asm volatile ("pop r24"::);\
} while (0)

//
// push+push+ldi+ldi+pop+pop = 2+2+1+1+2+2 = 10 cycles
// loop is sbiw+brne+(9+0xffff*4) = 2+2+9+4*65535 = 262.153 cycles
// except the last one which is one shorter,
// bringing the total to 9+262.153*us
#define DELAY_9P262153(i) \
do { \
	asm volatile ("push r24"::);\
	asm volatile ("push r25"::);\
	asm volatile("ldi r25, %0"::"M"(i>>8));\
	asm volatile("ldi r24, %0"::"M"(i&0xff));\
	DELAY_9P4(0xffff);\
	asm volatile("sbiw r24, 0x01");\
	asm volatile("brne .-20");\
	asm volatile ("pop r25"::);\
	asm volatile ("pop r24"::);\
} while (0)



