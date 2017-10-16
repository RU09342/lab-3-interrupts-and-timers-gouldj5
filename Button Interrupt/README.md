# LAB 3 - Button Interrupt
#### Joshua Gould
##### Created - 10-14-2017
##### Updated - 10-14-2017

## Library Used
msp430.h - default library

## Dependencies
* MSP430 Development board
* CCS coding software

## Set Requirements
"Your goal for this part of the lab is to replicate your button code from Lab 2, where the LED should change states only when the button is pressed. This can be extended to include behaviors such as only have the LED on when the button is depressed, or have the LED blink one color when pressed and another when it is let go. Another behavior extends from the second lab which is speed control based on the button presses. For example, have the rate of the LED cycle between a "low", "Medium", and "High" rate of speed."

#### Tasks
* [x] Toggle an LED using interrupts

## Compatibility
* MSP430F5529
* MSP430FR2311
* MSP430FR6989
* MSP430FR5594
* MSP430G2553

The pin assignments on each board can be different. Certain boards with FR require high impedence on a pin to be disabled. Certain boards use a different timer.

# Functionality Description
The LED in all processors change states only when the button is pressed. The program was used to understand interrupts. Both LEDs were used as outputs and the button set to input. Interrupts in this program was enabled and set on the falling edge as detailed in the comments of the code. The interrupts used an if else state to turn on either LED. In the 5529 code, the LEDs alternate on and off.

### Detailed Description

* Enable SetInterrupts (duh)
* Toggle LED within the interrupt
* Clear Button Flag

### Example Code
```C
#include <msp430.h>
/*
MSP430G2553
Button Interrupt
*/
#define BUTTON BIT3				//P1.3 BUTTON defined
#define LED   BIT6				//P1.6 LED green defined

void main(void) {
	WDTCTL = WDTPW | WDTHOLD;	//stop watchdog timer

	P1DIR |= LED;				//set LED pin to output
	P1DIR &= ~BUTTON;			//set button to input
	P1REN |= BUTTON;			//Enable pull-resistor
	P1OUT |= BUTTON;			//Make pull-resistor a pull-up

	P1IES &= ~BUTTON;			//Rising edge interrupt
	P1IE |= BUTTON;		 		//Enable interrupt on BUTTON

	_bis_SR_register(LPM4_bits + GIE);
								//Enter LPM4 and Enable CPU Interrupt
								// enables interupts
}

#pragma vector=PORT1_VECTOR		//interrupt vector PORT 1
_interrupt void Port_1(void)
{
	P1OUT ^= LED;				//Toggle green LED
	P1IFG &= ~BUTTON;			//Clear BUTTON interrupt flag
}
```