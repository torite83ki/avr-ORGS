/*
 *  avr_main.c
 *  device = at90s2313
 *
 *  used interrupts
 *  TIM0
 *  
 *  coded by H.Takenobu
 *  2020.12.13 rev.0
 *
 */


#define DBUG	1	/* 1:Enalble/0:disable debug function */

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h>
#include <util/delay.h>

/* 
 * user defined constant
 */
/* led is connected as sink-source */
#define LED1_PIN	2
#define LED2_PIN	3
#define LED3_PIN	6
#define LED4_PIN	7


#define HIGH	0x01
#define LOW	0x00


/*
 * interrupt handlers
 */
ISR(TIMER0_OVF0_vect);

/*
 * sub routines
 */
void init_port(void);

/*
 * sram static values
 */
//volatile uint16_t time_count;

/* main routine for avr */
int main(void){

	cli();
//	init_timer();
	init_port();

	sei();

/* debug */ 
#ifdef DEBUG
	DDRD  = 0xFF;
	DDRB  = 0xFF;
	PORTB = 0xF0;
	PORTD = 0x00;

	for(;;){
		PORTD = 0xAA;
		_delay_ms(100);
		_delay_ms(100);
		_delay_ms(100);
		PORTD = 0xCC;
		_delay_ms(100);
		_delay_ms(100);
	}
#endif

} /* end of main routine */

ISR(TIMER0_OVF0_vect) {


}
