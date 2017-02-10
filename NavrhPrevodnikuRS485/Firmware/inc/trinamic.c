/*
 * trinamic.c
 *
 * Created: 17.1.2017 13:27:56
 *  Author: atom2
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include "common_defs.h"
#include "def_init.h"
#include <avr/interrupt.h>
#include "trinamic.h"
#include "uart0.h"


volatile Trinamicpac TR_Buf_In;
uint8_t uart0_rx_ptr;
uint8_t uart0_buf_rx[BUFFER_CHAR_PACKET];

volatile Trinamicpac TR_Buf_Out;
uint8_t uart1_rx_ptr;
uint8_t uart1_buf_rx[BUFFER_CHAR_PACKET];

uint8_t TR_buf_fill_In()
{
	for (uint8_t i=9;i>0;i--)
	{
		TR_Buf_In.b[9-i] = uart0_buf_rx[uart0_rx_ptr-i];	 
	}
	if (uart0_rx_ptr > 17)
	{
		uart0_rx_ptr = 0;
	}
	return 1;
}

uint8_t TR_buf_fill_Out()
{
	for (uint8_t i=9;i>0;i--)
	{
		TR_Buf_Out.b[9-i] = uart1_buf_rx[uart1_rx_ptr-i];	 
	}
	if (uart1_rx_ptr > 17)
	{
		uart1_rx_ptr = 0;
	}
	return 1;
}

