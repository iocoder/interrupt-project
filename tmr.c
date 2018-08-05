/* ------------------------------------------ */
/*               Timer Driver                 */
/* ------------------------------------------ */

#include <avr/io.h>
#include <avr/interrupt.h>

#include "irq.h"
#include "tmr.h"

static volatile unsigned char trigger_callback   = 0;

void (*timer_handler)(void) = 0;

ISR(TIMER1_COMPA_vect)
{
    // trigger timer_handler
    trigger_callback++;
}

void tmr_init( void (*external_handler)(void) ) {
    // initialize timer hardware
    TCNT1  = 0; 
    OCR1A  = 15624 ; //setting compare value 
    TIMSK |= (1<<OCIE1A) ; //enable the required interrupt for ctc mode 
    TCCR1A = (0<<WGM10)|(0<<WGM11); 
    TCCR1B = (1<<CS11)|(1<<CS10)|(1<<WGM12)|(0<<WGM13) ; 
	// set timer callback
    timer_handler = external_handler;
}

void tmr_loop() {
    // sense trigger_callback
    if (trigger_callback) {
        // call timer_handler
        if (timer_handler != 0) {
            timer_handler();
        }
        // decrease the counter
		irq_disable();
		trigger_callback--;
		irq_enable();
    }
}
