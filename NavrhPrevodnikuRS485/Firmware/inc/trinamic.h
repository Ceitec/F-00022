/*
 * trinamic.h
 *
 * Created: 17.1.2017 13:27:46
 *  Author: atom2
 */ 


#ifndef TRINAMIC_H_
#define TRINAMIC_H_

#define RS485_EN_INT_receive		cbi(PORTD, PORTD4);
#define RS485_EN_INT_transmite		sbi(PORTD, PORTD4);

#define RS485_EN_EXT_receive		cbi(PORTD, PORTD5);
#define RS485_EN_EXT_transmite		sbi(PORTD, PORTD5);


typedef union {
	struct {
		uint8_t addr;
		uint8_t cmd;
		uint8_t type;
		uint8_t motor;
		union {
			uint32_t dw;
			struct {
				uint8_t b0;
				uint8_t b1;
				uint8_t b2;
				uint8_t b3;
			} b;
		} val;
		uint8_t uart0_sum;
	} n;
	uint8_t b[9];
} Trinamicpac;


#endif /* TRINAMIC_H_ */