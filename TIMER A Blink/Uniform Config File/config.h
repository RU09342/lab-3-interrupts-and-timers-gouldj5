//credit to RyanH98 for reference
//link: https://github.com/RU09342/lab-3-interrupts-and-timers-RyanH98/tree/master/TIMER%20A%20Blink
/*
*config file for uniform conversion between boards
*/

#ifndef CONFIG_H_
#define CONFIG_H_

#if defined(__MSP430G2553__)
    #include <msp430g2553.h>		//extended reference for G2

    #define LED0 BIT0		//Define bits for the LEDs and BUTTON.
    #define LED1 BIT1
    #define BUTTON BIT3

    #define LEDDIR P1DIR	//Define DIR and OUT for the correct LED1 pin.
    #define LEDOUT P1OUT

    #define BTNDIR P1DIR		//Define button pin outs.
    #define BTNREN P1REN
    #define BTNOUT P1OUT
    #define BTNIE P1IE
    #define BTNIES P1IES
    #define BTNIFG P1IFG
    #define BTNIN P1IN

#elif defined(__MSP430F5529__)
    #include <msp430f5529.h>		//extended reference for 5529

    #define LED0 BIT0
    #define LED1 BIT7
    #define BUTTON BIT1

    #define LEDDIR P4DIR
    #define LEDOUT P4OUT

    #define BTNDIR P2DIR
    #define BTNREN P2REN
    #define BTNOUT P2OUT
    #define BTNIE P2IE
    #define BTNIES P2IES
    #define BTNIFG P2IFG
    #define BTNIN P2IN
		
#elif defined(__MSP430FR6989__)
    #include <msp430fr6989.h>		//extended reference for 6989
    #define LED0 BIT0
    #define LED1 BIT7
    #define BUTTON BIT1

    #define LEDDIR P9DIR
    #define LEDOUT P9OUT

    #define BTNDIR P1DIR
    #define BTNREN P1REN
    #define BTNOUT P1OUT
    #define BTNIE P1IE
    #define BTNIES P1IES
    #define BTNIFG P1IFG
    #define BTNIN P1IN

#elif defined(__MSP430FR5994__)
    #include <msp430fr5994.h>		//extended reference for 5994

    #define LED0 BIT0
    #define LED1 BIT2
    #define BUTTON BIT6

    #define LEDDIR P1DIR
    #define LEDOUT P1OUT

    #define BTNDIR P5DIR
    #define BTNREN P5REN
    #define BTNOUT P5OUT
    #define BTNIE P5IE
    #define BTNIES P5IES
    #define BTNIFG P5IFG
    #define BTNIN P5IN

#elif defined(__MSP430FR2311__)
    #include <msp430fr2311.h>		//extended reference for 2311

    #define LED0 BIT0
    #define LED1 BIT1
    #define BUTTON BIT1

    #define LEDDIR P4DIR
    #define LEDOUT P4OUT

    #define BTNDIR P1DIR
    #define BTNREN P1REN
    #define BTNOUT P1OUT
    #define BTNIE P1IE
    #define BTNIES P1IES
    #define BTNIFG P1IFG
    #define BTNIN P1IN

#else
  #error "Unsupported board detected!"
#endif

#endif /* CONFIG_H_ */