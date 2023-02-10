/*
 * HackySerial.h
 *
 *  Created on: 7 Feb 2023
 *      Author: Notandi
 */

#ifndef HACKYSERIAL_H_
#define HACKYSERIAL_H_

#include <avr/io.h>
// for printing to serial::
// USART code taken from datasheet for printing to serial
#define FOSC 16000000 // Clock Speed
#define BAUD 9600

//#define MYUBRR FOSC / 16 / BAUD - 1
// dont trust the compiler to calculate that correctly so
#define MYUBRR 103



#define USART_INIT \
do{\
  /*Set baud rate */\
  UBRR0H = (unsigned char)(MYUBRR >> 8);\
  UBRR0L = (unsigned char)MYUBRR;\
  /* Enable receiver and transmitter */\
      UCSR0B = (1 << RXEN0) | (1 << TXEN0);\
  /* Set frame format: 8data, 2stop bit */\
  UCSR0C = (3 << UCSZ00);\
} while (0)

#define USART_TRANSMIT(data)\
do {\
  /* Wait for empty transmit buffer */\
  while (!(UCSR0A & (1 << UDRE0)))\
    ;\
  /* Put data into buffer, sends the data */\
  UDR0 = data;\
} while (0)

#define USART_REC_READY (UCSR0A & (1 << RXC0))

unsigned char USART_Receive(void)
{
  /* Wait for data to be received */
  while (!USART_REC_READY)
    ;
  /* Get and return received data from buffer */
  return UDR0;
}


#define PRINTLN() USART_Transmit(10)

//void print(unsigned char arr[], int size)
//{
//  for (int i = 0; i < size; i++)
//  {
//    USART_Transmit(arr[i]);
//  }
//}

//void println(unsigned char arr[], int size)
//{
//  print(arr, size);
//  println();
//}

// helper function to print an integer
void print_i(unsigned int i)
{
  // special case for when i is 0
  if (i == 0){
    USART_TRANSMIT('0');
    //USART_Transmit((unsigned char)10);
    return;
  }
  // if negative print minus sign and then just as if it were positive
  if (i < 0){
    USART_TRANSMIT('-');
    i = -i;
  }
  // don't print leading zeros, however,do print zeros that are not leading
  char leading_zeros_done = 0;
  int m = 10000;
  for (int j = 4; j>= 0;j--) // supports 5 digit numbers (ints can't be larger)
  {
    if (leading_zeros_done || i/m > 0){
      USART_TRANSMIT(((i/m)%10) + 48);
      leading_zeros_done = 1;
    }
    m /= 10;
  }
}

//void print_3_numbers(int32_t a, int32_t b, int32_t c)
//{
//  print_i(a);
//  print_one('\t');
//  print_i(b);
//  print_one('\t');
//  print_i(c);
//  print_one('\n');
//}
//void print_i_ln(int32_t i)
//{
//  print_i(i);
//  println();
//}



#endif /* HACKYSERIAL_H_ */
