#ifndef _MSP430_DEBUG
#define _MSP430_DEBUG

#include <intrinsics.h>
#include <string.h>
#include <msp430.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "USB/USB_config/descriptors.h"
#include "USB/USB_API/USB_Common/device.h"
#include "USB/USB_API/USB_Common/types.h"               //Basic Type declarations
#include "USB/USB_API/USB_Common/usb.h"                 //USB-specific functions
#include "USB/USB_API/USB_CDC_API/UsbCdc.h"
#include "USB/usbConstructs.h"

#include "F5xx_F6xx_Core_Lib/HAL_UCS.h"
#include "F5xx_F6xx_Core_Lib/HAL_PMM.h"

#include "wdt.h"

__attribute__((critical)) int16_t usb_printf(const char * fmt);
/** \fn DEBUG 
 *  \brief DEBUG output. 
 *
 *  Could be used with some more logic, like
 *  only printing the output if the USB connection is present,
 *  or having different verbose levels */
// USB debug:
// #define DEBUG(...) do {usb_printf(__VA_ARGS__);} while(0);
#define DEBUG usb_printf

#define USB_LOCKED   2
#define USB_ENABLED  1
#define USB_DISABLED 0

/** The maximum length of a string that is
  * processed through the interface */
#define MAX_STR_LENGTH 32

/** This function is used intensively through
    TI's libraries, but I adopted a simpler
    approach */
#ifndef __even_in_range
#define __even_in_range(a,b) (a)
#endif

//Function declarations
void usb_printf_init(void);
void usb_receive_string(void);

#endif
