/* ------------------------------------------ */
/*              IRQ Controller                */
/* ------------------------------------------ */

#include <avr/interrupt.h>

#include "irq.h"
 
 void irq_disable() {
	 cli();
 }
 
  void irq_enable() {
	 sei();
 }
 