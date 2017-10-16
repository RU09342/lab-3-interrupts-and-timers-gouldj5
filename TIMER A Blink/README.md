# LAB 3 - TIMER A Blink
#### Joshua Gould
##### Created - 10-15-2017
##### Updated - 10-16-2017

## Library Used
msp430.h - default library including extra work

## Dependencies
* MSP430 Development board
* CCS coding software

## Set Requirements
"Using the TIMER module instead of a software loop, control the speed of two LEDS blinking on your development boards. Experiment with the different counting modes available as well as the effect of the pre-dividers. Why would you ever want to use a pre-divider? What about the Capture and Compare registers? Your code should include a function (if you want, place it in its own .c and .h files) which can convert a desired Hz into the proper values required to operate the TIMER modules."

#### Tasks
* [x] Control the speed of two LEDS blinking on your development boards
* [x] Use the TIMER module
* [x] Extra Work

## Compatibility
* MSP430F5529
* MSP430FR2311
* MSP430FR6989
* MSP430FR5594
* MSP430G2553

# Functionality Description
Control the speed of two LEDS blinking on your development boards using the TIMER modules

### Detailed Description
Timers can be used as a powerful tool in syncronization, organizing, and counting. The MSP430 uses SMCLK, ACLK, TACLK, and external clocks in its design. Clocks used in this code are provided below.
* Define GPIO
* Enable interrupt
* Define Clock at 1MHZ and devide by 8
```C
TACTL = TASSEL_2 + MC_1 + ID_3; // SMCLK = 1MHZ -> TASSEL_2
									// UPMODE -> Mc_1
									// ID_3 devides SMCLK by 8 I_(11_2)
	int capture = (125000) / hertz;  //manage frequency
	TACCR0 = capture; // (1000000/8)/(12500) = 10 Hz = 0.1 seconds
					  // CLK = 1MHZ/8 = 12.5kHz
```
* Use clock to provide LED toggle
### Example Code
```C
#include <msp430.h>
/*
MSP430G2553
Timer A Blink
*/
#define LED0 BIT0		// definitions of pins
#define LED1 BIT6

void initTimer(int capture); //function calling capture

unsigned int timerCount = 0; //check unsigned and initialize 

void main(void)
{
	WDTCTL = WDTPW + WDTHOLD; // Stop watchdog
	P1DIR |= (LED0 + LED1); // Set P1.0 & P1.6 to output direction
	P1OUT &= ~(LED0 + LED1); // Start LED off

	initTimer(20); // Initialize timer at 10Hz or 0.1s

	__enable_interrupt();

	__bis_SR_register(LPM0 + GIE); // LPM0 with interrupts enabled
}

void initTimer(int hertz) //hertz pertains to clock time
{
	CCTL0 = CCIE;					// CCR0 interrupt enabled
	TACTL = TASSEL_2 + MC_1 + ID_3; // SMCLK = 1MHZ -> TASSEL_2
									// UPMODE -> Mc_1
									// ID_3 devides SMCLK by 8 I_(11_2)
	int capture = (125000) / hertz;  //manage frequency
	TACCR0 = capture; // (1000000/8)/(12500) = 10 Hz = 0.1 seconds
					  // CLK = 1MHZ/8 = 12.5kHz
}

// TimerA0 interrupt sequence
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0(void)
{
	if (timerCount >= 25) //set timer cycle period
	{
		P1OUT ^= (LED0 + LED1); //toggle on LED
		timerCount = 0; //Reset timer
	}
	else timerCount++; //increment until ~2.5s
}
```

# Extra Work Description

#### Working with HALs
This section of the project uses a seperate header file to uniformly organize the BITs of each processor at our desposal. After defining how to call each section, normal definitions are provided. Inside each code, the file will just need to call msp430XXXXX.h and recieve definitions

#### Example Code
```C
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
```