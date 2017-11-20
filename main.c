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

int main()
{
	initUART();
	RX_INTEN();//enable RX interrupt
	sei();
	while(1)
	{
		//main loop
	}
}
ISR(USART_RX_vect)
{
	LED_TOGGLE();
	char c = getByte();
	switch(c)
	{
	case 13://CR
		writeString("\r\n");
		break;
	default:
		putByte((char)'X');
		break;
	}
}
