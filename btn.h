#ifndef __BTN_H
#define __BTN_H

void btn_init( void (*external_handler)(void) );
int  btn_get_state();
void btn_loop();

#endif /* __BTN_H */
