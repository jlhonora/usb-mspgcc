#ifndef __MSP430_UTILS
#define __MSP430_UTILS
/** \file utils.h
 *  \brief Different utils used throughout the program
 */
#include <msp430.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "usb_printf.h"
/** For jumping into bsl section */
void            msp_reset_to_bsl(void);

#ifndef interrupt
#define interrupt(x) void __attribute__((interrupt (x)))
#endif

#endif
