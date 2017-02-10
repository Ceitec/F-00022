/*
 * def_init.h
 *
 * Created: 16.1.2017 17:57:17
 *  Author: atom2
 */ 


#ifndef DEF_INIT_H_
#define DEF_INIT_H_

//Velikost použitého krystalu
#define F_CPU 16000000UL

//Velikost bufferu pro pøíjem dat
#define	BUFFER_CHAR_PACKET	18 // Musí být násobky 9!!!

#define LED2_ON		sbi(PORTD, PORTD6);
#define LED2_OFF	cbi(PORTD, PORTD6);
#define LED1_ON		sbi(PORTD, PORTD7);
#define LED1_OFF	cbi(PORTD, PORTD7);



#endif /* DEF_INIT_H_ */