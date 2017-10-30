/*
 * UART_TEST
 * main.c
 *
 *  Created on: 29 paź 2017
 *      Author: zbyszek
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart.h"
#include <string.h>
#include <stdio.h>

#define LED_DDR DDRB
#define LED_PORT PORTB
#define LED_PIN PB5
#define LED_TOGGLE() (LED_PORT ^= 1<<LED_PIN)

#define BUFF_SIZE 16
char buff[BUFF_SIZE];	//Buffer for serial data
uint8_t BI = 0;			//Buffer Index

int main()
{
	initUART();
	RX_INTEN();//enable RX interrupt
	sei();
	while(1)
	{
		//main loop
//		writeString(buff);
//		_delay_ms(500);
	}
}
ISR(USART_RX_vect)
{
	LED_TOGGLE();
	char c = getByte();
	switch(c)
	{
	case 13://CR
		if(BI==0) break;// you you didn't enter anything, don't do anything.
		writeString("\r\n");
		//do sth with entered data
		writeString("\e[1;1H\e[2J"); //clear console
		char msgBuff[30];
		sprintf(msgBuff, "You entered: %s\n\rType in the speed:", buff);
		writeString(msgBuff);
		//
		memset(buff,0 , sizeof(buff));// "zero" the buffer
		BI = 0;
		break;
	case 48 ... 57:
		if(BI < BUFF_SIZE-1)//leave 1 byte for trailing \n
		{
			putByte(c);
			buff[BI++] = c;
		}
		//else putByte((char)'X');
		break;
	default:
		break;

	}
}
