#ifndef __TMR_H
#define __TMR_H

void tmr_init( void (*external_handler)(void) );
void tmr_loop();

#endif /* __TMR_H */
