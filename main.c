/* ------------------------------------------ */
/*                Main Loop                   */
/* ------------------------------------------ */

#include "irq.h"
#include "btn.h"
#include "led.h"
#include "tmr.h"
 
void tmr_callback() {
    // this code is triggered every 1s.
    int btn_state = btn_get_state();
    // toggle ONLY IF button is released
    if (!btn_state) {
        // button is now released
        led_toggle();
    }
}

void btn_callback() {
    // this code is triggered by button change 
    int btn_state = btn_get_state();
    // if new button state is PRESSED, set leds to 1
    if (btn_state) {
        // button is now pressed
        led_on();
    }    
}

int main(void) {
    // initialize hardware
    irq_disable();
    led_init();
    btn_init(&btn_callback);
    tmr_init(&tmr_callback);
    irq_enable();
    // system loop
    while (1) {
        // execute button driver
        btn_loop();
        // execute leds driver
        led_loop();
        // execute timer driver
        tmr_loop();
    }
    // code should never reach this line
    return 1; 
}
