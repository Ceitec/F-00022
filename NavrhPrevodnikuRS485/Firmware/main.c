/*
 * Firmware.c
 *
 * Created: 16.1.2017 17:16:21
 * Author : atom2
 */ 

/*
Nastaven� fuse bits
	High		0x91
	Low			0xD7
	Extended	0xFC
	Bez Bootloader re�imu
*/



#include <avr/io.h>

#include "inc/def_init.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <avr/eeprom.h>
#include <avr/wdt.h>
#include <string.h>
#include "inc/common_defs.h"
#include "inc/def_init.h"
#include "inc/uart0.h"
#include "inc/uart1.h"
#include "inc/trinamic.h"
#include "inc/timer.h"


uint8_t uart0_error=0,uart1_error=0;

// Deklarov�n� prom�nn�ch z uart0.c
uint8_t uart0_rx_ptr;
uint8_t uart0_buf_rx[BUFFER_CHAR_PACKET];
uint8_t uart1_buf_tx[BUFFER_CHAR_PACKET];

uint8_t uart1_rx_ptr;
uint8_t uart1_buf_rx[BUFFER_CHAR_PACKET];
uint8_t uart1_buf_tx[BUFFER_CHAR_PACKET];

uint8_t uart1_tx_flag;
uint8_t uart1_tx_iptr;

uint8_t uart1_rx_flag;
uint8_t uart1_rx_iptr;

uint8_t uart0_tx_flag;
uint8_t uart0_tx_ptr;
uint8_t uart0_tx_iptr;

uint8_t uart0_rx_flag;
uint8_t uart0_rx_ptr;
uint8_t uart0_rx_iptr;


Trinamicpac TR_Buf_In;
Trinamicpac TR_Buf_Out;


#define ADDRESS_EXT 100


uint32_t UB = 0;

uint16_t citacka0, citacka1;

int main(void)
{
	
	UB = UART0_DEFAULT_BAUD;
	uart0_error = uart0_init(UB);
	UB = UART1_DEFAULT_BAUD;
	uart1_error = uart1_init(UB);
	uart0_interrupt_rx(TRUE);
	uart0_interrupt_tx(TRUE);
	uart1_interrupt_rx(TRUE);
	uart1_interrupt_tx(TRUE);
	
	
	//Pokud by nastal n�jak� error p��padn� roz���en� knihovny
	//if uart0_error != 0
	
	// Nastaven� RS485 Enable
	sbi(DDRD, DDD4);
	// Nastaven� RS485 Enable
	sbi(DDRD, DDD5);
	// UART0 RX
	cbi(DDRD, DDD0);
	// UART1 RX
	cbi(DDRD, DDD2);
	// UART0 TX
	sbi(DDRD, DDD1);
	// UART1 TX
	sbi(DDRD, DDD3);
	// LED1
	sbi(DDRD, DDD6);
	// LED2
	sbi(DDRD, DDD7);
	
	cbi(PORTD, PORTD7);
	cbi(PORTD, PORTD6);
	

	
	// Povolen� p�ijmu dat
	RS485_EN_INT_receive;
	RS485_EN_EXT_receive;
	
	// Povolen� glob�ln�ho p�eru�en�
	sei();
	uint8_t j=0;
	
	// Hlavn� smy�ka programu
	while (1) 
    {
		//uart1_transmit_char(0x01);
		//RS485_EN_INT_receive;
// 		_delay_ms(500);
// 		RS485_EN_INT_transmite;
// 		uart0_tx_flag=true;
// 		UART0_UDR = 0x02;
// 		
// 		RS485_EN_EXT_transmite;
// 		uart1_tx_flag=true;
// 		UART1_UDR = 0x01;
		

		j = check_uart0();
 		if (j==1)
 		{
			// Napln� Buffer trinamic
			TR_buf_fill_In();
			// Kontrola adresy
			if (TR_Buf_In.n.addr >= ADDRESS_EXT)
			{
				// Povolen� odes�l�n� dat na extern� linku
				uart1_tx_flag=TRUE;
				RS485_EN_EXT_transmite;
				UART1_UDR = TR_Buf_In.b[uart1_tx_iptr++];
			}
 		}
		// Odesl�n� uart1 na uart0, nebo-li data z extern� RS485 na Intern�.
 		// check_uart1();

		j = check_uart1();
 		if (j==1)
 		{
			 
			// Napln� Buffer trinamic
			TR_buf_fill_Out();
			// Kontrola adresy
			// Povolen� odes�l�n� dat na extern� linku (Nastartov�n� p�eru�en�)
			uart0_tx_flag=TRUE;
			RS485_EN_INT_transmite;
			// Odesl�n� prvn�ho Bytu
			UART0_UDR = TR_Buf_Out.b[uart0_tx_iptr++];
 		}		

		if (citacka0 > 10000)
		{
			LED2_OFF;
			// Vyma�e ka�d�ch 50ms flag intern� ��ta�
			uart0_rx_iptr=0;
			uart0_rx_ptr=0;
			citacka0=0;
		}
		LED2_ON;
		citacka0++;

		if (citacka1 > 10000)
		{
			// Vyma�e ka�d�ch 50ms flag intern� ��ta�
			LED1_OFF;
			uart1_rx_iptr=0;
			uart1_rx_ptr=0;
			citacka1=0;
		}
		LED1_ON;
		citacka1++;
		

		

// 
// 
// 		if (uart1_rx_flag)
// 		{
// 			//Odesl�n� 9 byt� dat
// 			if (uart0_tx_iptr > 8)
// 			{
// 				// Vypnut� odes�l�n� a povolen� p��jmu
// 				uart1_rx_flag = FALSE;
// 				RS485_EN_INT_receive;
// 				uart0_tx_iptr=0;
// 			}
// 			else
// 			{
// 				RS485_EN_INT_transmite;
// 				uart0_tx_flag=true;
// 				UART0_UDR = uart0_buf_rx[uart0_tx_iptr++];
// 			}
// 		}
		

    }
}

