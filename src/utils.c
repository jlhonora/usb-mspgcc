/** \file utils.c
 *  \brief Different utils used throughout the program
 */
#include <stdlib.h>
#include <stdint.h>
#include <msp430.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"

/** Jumps into BSL routine */
__attribute__((critical)) void msp_reset_to_bsl(void) {
    // Disable USB connections
    USB_disconnect();
    USB_disable();
    // Unprotect BSl section
    SYSBSLC &= ~(SYSBSLPE);
    // Jump to BSL area
    ((void (*)())0x1000)(); 
}
