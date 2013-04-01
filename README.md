USB CDC support for msp430 using mspgcc
======================================

The following code implements a USB CDC device than can be used as a serial port to send and receive data to a msp430 microcontroller.

This repo is a modification of the [USB Developer's package for MSP430](http://www.ti.com/tool/msp430usbdevpack) from Texas Instruments to compile it with [mspgcc uniarch](http://mspgcc.sourceforge.net/) (C compiler for [msp430](http://www.ti.com/msp430) microcontrollers). 

To use this library you need to [install mspgcc](https://github.com/jlhonora/mspgcc-install) and the __rake__ utility:

    $ sudo apt-get install rake

## Using the program ##

First, build the example:

    $ rake

And install it:

    $ sudo mspdebug rf2500 "prog bin.elf"

A USB interface should appear in your PC. Using a serial port terminal software such as Coolterm or minicom you should be able to send and receive characters. A simple console is implemented, and can be entered sending 'shell\r\n'. More commands can be added in the console.c file.

This code can be used as a starting point for other USB interfaces, such as HID or MSC, for example. To create your own descriptor string you should use TI's USB descriptor tool.

## Troubleshooting ##

I've only tested this code with an msp-exp430f5529 experimenter board and a custom board using the msp430f5528 uC in Ubuntu and OS X. Feel free to add issues as long as you encounter them, I'll try to address them as soon as possible.
