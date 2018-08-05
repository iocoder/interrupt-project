/* ------------------------------------------ */
/*               Button Driver                */
/* ------------------------------------------ */

#include <avr/io.h>
#include <avr/interrupt.h>

#include "irq.h"
#include "btn.h"
 
static volatile unsigned char internal_btn_state = 0;
static volatile unsigned char trigger_callback   = 0;

void (*btn_handler)(void) = 0;

ISR(INT0_vect,ISR_NOBLOCK)
{
    // set button new state
    internal_btn_state ^= 1; 
	// trigger callback function
	trigger_callback++;
}

void btn_init( void (*external_handler)(void) ) {
    // initialize btn pin direction
    DDRD  &= ~(1<<2); 
    // configuring btn interrupt
    MCUCR |= (1<<ISC00)|(0<<ISC01); // any edge
    GICR  |= (1<<INT0); // enable int0
    // Assume initial state:
    if ( (PIND&(1<<2)) ) {
        // button is pressed
        internal_btn_state = 1;
    } else {
        // button is released
        internal_btn_state = 0;
    }
	// set callback
    btn_handler = external_handler;
}

int btn_get_state() {
    // just return btn state (handled internally by the driver)
    return internal_btn_state;
}

void btn_loop() {
    // sense trigger_callback
	if (trigger_callback) {
		// call btn_handler function
		if (btn_handler != 0) {
			btn_handler();
		}
		// decrease the callback counter
		irq_disable();
		trigger_callback--;
		irq_enable();
	}
}
