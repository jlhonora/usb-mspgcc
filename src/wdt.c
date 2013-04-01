/** \file wdt.c
 *  \brief Starts and stops the watchdog timer
 *  as WDT (and not as a timer)
 */
#include "wdt.h"


/** Stops the watchdog */
void wdt_stop(void) {
	WDTCTL = WDTPW | WDTHOLD;
    SFRIE1 &= ~WDTIE;
}

/** Starts the watchdog timer in WDT mode in 1 second interval*/
void wdt_start(void) {
	// WDT in watchdog mode, sourced from ACLK, 32768 divider
	// 1 second interval
	WDTCTL = WDT_WDT_CONFIG;
    SFRIE1 &= ~WDTIE;
}

/** This variable is used to check if the main loop
 * is working. If the variable reaches WDT_MAX_COUNTER
 * the uC will be reset */
volatile uint16_t wdt_counter = 0;
void wdt_as_safe_timer(void) {
    WDTCTL = WDT_TIMER_CONFIG;
    SFRIE1 |= WDTIE;
}

#ifndef interrupt
#define interrupt(x) void __attribute__((interrupt (x)))
#endif
interrupt(WDT_VECTOR) WDT_ISR() {
    if(wdt_counter++ > WDT_MAX_COUNTER) {
        // Writing a value to WDTCL with no
        // password causes a reset
        WDTCTL = 0;
    }
}
