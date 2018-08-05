/* ------------------------------------------ */
/*                LED Driver                  */
/* ------------------------------------------ */

#include <avr/io.h>

#include "led.h"

void led_init() {
    // leds direction
    DDRA  |= (1<<0)|(1<<1)|(1<<2)|(1<<3);
    // leds initial state
    PORTA = 0;
}

void led_on() {
    PORTA = 0x0F;
}

void led_off() {
    PORTA = 0x00;    
}

void led_toggle() {
    PORTA ^= 0x0F;
}

void led_loop() {
    // do nothing
}
 