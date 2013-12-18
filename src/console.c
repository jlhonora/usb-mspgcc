#include "console.h"
/** \file console.c
  * \brief Implements a simple console for
  * the microcontroller. Each command
  * should be sent in a single packet,
  * not character-by-character. */

uint8_t console_execute_command(void);
void console_wait_for_newline(void);
void console_print_header(void);
void console_reset_command(void);
void console_reset_command(void);

/** Enters console mode */
void console(void) {
    uint8_t console_exit = 0;
    while(1) {
        console_print_header();
        console_wait_for_newline();
        console_exit = console_execute_command();
        console_reset_command();
        if(console_exit) return;
    }
}

void console_print_header(void) {
    DEBUG("user# ");
}

extern volatile BYTE bCDCDataReceived_event;   
char command[MAX_STR_LENGTH];
uint16_t command_len = 0;

/** This command should append characters to
  * the command array until a newline is
  * received. This functionality is not
  * implemented yet. */
void console_wait_for_newline(void) {
    while(1) {
        if(bCDCDataReceived_event == TRUE) {
            if(command_len >= MAX_STR_LENGTH) {
                command_len = 0;
            }
            command_len += cdcReceiveDataInBuffer((BYTE*)(command + command_len),
                                   MAX_STR_LENGTH - command_len,
                                   CDC0_INTFNUM);
            // Echo the command
            DEBUG(command);
            bCDCDataReceived_event = FALSE;
            return;
        }
    }
}

/** Commands that will be recognized by the 
  * microcontroller. */
uint8_t console_execute_command(void) {
    if(strncmp(command, "quit", 4) == 0) {
        DEBUG("Logging out\r\n");
        return 1;
    }
    if(strncmp(command, "exit", 4) == 0) {
        DEBUG("Logging out\r\n");
        return 1;
    }
    if(strncmp(command, "bsl", 3) == 0) {
        DEBUG("Entering bsl\r\n");
        __delay_cycles(1000);
        msp_reset_to_bsl();
        return 0;
    }
    DEBUG("Unknown command\r\n");
    return 0;
}

/** Clear the command array */
void console_reset_command(void) {
    command_len = 0;
    command[0] = 0;
}

