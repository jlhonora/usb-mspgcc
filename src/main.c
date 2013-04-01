/** The following code uses TI's USB library
 *  for MSP430 to enable printf functionalities
 *  in the microcontroller.  It uses a USB CDC 
 *  interface to create a serial port, which
 *  can be accessed with standard software
 *  such as CoolTerm, HyperTerm, etc.
 *
 *  Please note that this library only works 
 *  in microcontrollers with USB capabilities, 
 *  such as the msp430f552x series.
 *
 *  To build it, just run:
 * 
 *  rake
 *
 *  To install it in the msp-exp430f5529 board:
 *  sudo mspdebug rf2500 "prog bin.elf"
 *
 *  This code was modified from the USB
 *  Developers Package available from the TI
 *  website. This code is provided as-is
 *  and comes with no warranty or support
 *  whatsoever. You are free to use it as long
 *  as you cite this work.
 *
 *  Enjoy!
 *
 *  Jose L. Honorato
 *  April, 2013
 */

#include <msp430.h>
#include <stdint.h>

#include "usb_printf.h"

//Indicates data has been received without an open rcv operation
volatile BYTE bCDCDataReceived_event = FALSE;   

// Function declarations
void msp_init(void);
uint8_t events_available(void);
void process_events(void);

// To activate testing the rake command
// should be invoked like this:
// rake test=1
#ifdef TESTING
#include "test.h"
#endif

int main(void) {
    // If TESTING is defined at compile time then
    // we don't run the main application
    // This can be done by executing
    // rake test=1
#ifdef TESTING
    return test();
#endif
    // Initialize the different parts
    msp_init();

    DEBUG("Running\r\n");

    // Main loop
    while(1) {  
        // Check if there are events available. If there are
        // then we process them
        if(events_available()) {
            process_events();
        }
    }
}

/** Initializes modules and pins */
void msp_init(void) {
    // Stop the watchdog
    wdt_stop();
    // Initialize USB interface
    usb_printf_init();
    // Enable global interrupts
    __enable_interrupt();
}

/** Checks if there are events available to be processed
 * The currently supported events are:
 * - There are USB packets available
 *
 *   These events are checked quite frequently because the main
 *   loop is constantly checking them. Anyhow, whenever we need to process
 *   a lengthy task, the main loop will cease to check for an event. 
 *   This doesn't mean that the events will be dropped, but they will 
 *   not be managed instantly.
 */
uint8_t events_available(void) {
    return (
        //data received event
        bCDCDataReceived_event
        );
}

/** Process then events queried in the \ref events_available() function */
void process_events(void) {
    // Data received from USB
    if(bCDCDataReceived_event == TRUE) {
        usb_receive_string();
    }   
}
