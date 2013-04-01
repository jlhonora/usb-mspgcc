#include "usb_printf.h"
void init_ports(void);
void init_clock(void);

volatile uint8_t usb_printf_state = USB_DISABLED;
__attribute__((critical)) int16_t usb_printf(const char * fmt, ...) {
    if(usb_printf_state == USB_DISABLED) return -1;
    if(usb_printf_state == USB_LOCKED) return -1;
    usb_printf_state = USB_LOCKED;
    int16_t len;
    va_list args;
    va_start(args, fmt);
    char msg[64];
    len = vsnprintf(msg, 64, fmt, args);
    cdcSendDataWaitTilDone((BYTE*) msg,
                            len, CDC0_INTFNUM, 1);
    va_end(args);
    usb_printf_state = USB_ENABLED;
    return len;
}

void usb_printf_init(void) {
    SetVCore(3);
    init_clock();
    //Init USB
    USB_init();                 
    //Enable various USB event handling routines
    USB_setEnabledEvents(kUSB_VbusOnEvent + 
                         kUSB_VbusOffEvent + 
                         kUSB_receiveCompletedEvent + 
                         kUSB_dataReceivedEvent + 
                         kUSB_UsbSuspendEvent + 
                         kUSB_UsbResumeEvent +
                         kUSB_UsbResetEvent);
    // See if we're already attached physically to USB, and if so, 
    // connect to it. Normally applications don't invoke the event 
    // handlers, but this is an exception.
    if(USB_connectionInfo() & kUSB_vbusPresent) {
        usb_printf_state = USB_ENABLED;
        USB_handleVbusOnEvent();
    }
}

void init_clock(void) {
    //enable XT2 pins for F5529
    P5SEL |= 0x0C;

    //use REFO for FLL and ACLK
    UCSCTL3 = (UCSCTL3 & ~(SELREF_7)) | (SELREF__REFOCLK);
    UCSCTL4 = (UCSCTL4 & ~(SELA_7)) | (SELA__REFOCLK);

    //MCLK will be driven by the FLL (not by XT2), referenced to the REFO
    //Start the FLL, at the freq indicated by the config
    //constant USB_MCLK_FREQ
    //Init_FLL_Settle(USB_MCLK_FREQ / 1000, USB_MCLK_FREQ / 32768);   
    //Start the "USB crystal"
    XT2_Start(XT2DRIVE_0);                                          
}

extern volatile BYTE bCDCDataReceived_event;   
void usb_receive_string(void) {
    uint8_t msg_len = 0;
    char msg[MAX_STR_LENGTH];
    //Get the next piece of the string
    msg_len = cdcReceiveDataInBuffer((BYTE*)msg,
        MAX_STR_LENGTH - 1,
        CDC0_INTFNUM);                                                         
    msg[msg_len] = 0;
    bCDCDataReceived_event = FALSE;
    if(strncmp(msg, "shell", 5) == 0) {
        DEBUG("Entering shell\r\n");
        console();
    } else {
        DEBUG("USB (l=%d): %s\r\n", msg_len, msg);
    }
}
