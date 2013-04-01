#ifndef __MSP430_WDT
#define __MSP430_WDT

#include <stdint.h>
#include <msp430.h>
#include "utils.h"

void wdt_stop(void);
void wdt_start(void);
void wdt_as_safe_timer(void);

#define WDT_WDT_CONFIG WDT_ARST_1000
#define WDT_TIMER_CONFIG WDT_ADLY_1000
/** Counter in seconds before resetting the uC */
#define WDT_MAX_COUNTER 300

#endif // _MSP430_WDT
