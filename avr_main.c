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



#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h>
#include <util/delay.h>
#include <avr/sleep.h>

/* 
 * user defined constant
 */

#define DEBUG	1	/* 1:Enalble/0:disable debug function */

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
void init_timer(void); 

/*
 * sram static values
 */
//volatile uint16_t time_count;

/* main routine for avr */
int main(void){

	cli();
	init_timer();
	init_port();

/* debug */ 
#ifdef DEBUG
	//DDRD  = 0xFF;
	//DDRB  = 0xFF;
	//PORTB = 0xF0;
	//PORTD = 0x00;
	uint8_t n;
	for(n = 0;n < 5;n++){
		PORTD = 0xAA;
		_delay_ms(100);
		_delay_ms(100);
		_delay_ms(100);
		PORTD = 0xCC;
		_delay_ms(100);
	}
#endif
	sei();
	for(;;) {
		sleep_mode();
	}

} /* end of main routine */


void init_port(void){
	DDRD = 0xFF;				/* PORTD: set 1 as output , all ports are output*/ 
	PORTD = 0xAA;				/* set LED pattern */
}

#define T0_OVF	247			/* Timer 0 overflow value -> 1ms */
void init_timer(void) {
	/* Timer 0 setting */
	TCCR0 = _BV(CS02) | _BV(CS00);		/* set prescaler 1/1024 */
	TCNT0 = T0_OVF;				/* set overflow count */
	TIMSK |= _BV(TOIE0);			/* set timer overflow interrupt enable */
}

static volatile uint16_t counter_ms = 0;		/* counter *ms  */
static volatile uint16_t counter_upperlimit = 500;		/* counter upper limit*/
ISR(TIMER0_OVF0_vect) {
	TCNT0 = T0_OVF;						/* set overflow value -> 1ms */
	if (++counter_ms >= counter_upperlimit) {
		counter_ms = 0;
		PORTD = ~PIND;
	}
}
