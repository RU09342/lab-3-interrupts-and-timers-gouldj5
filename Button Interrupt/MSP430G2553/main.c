#include <msp430.h>
/*
MSP430G2553
Button Interrupt
*/
#define BUTTON BIT3		//P1.3 BUTTON defined
#define LED   BIT6		//P1.6 LED green defined

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

#pragma vector=PORT1_VECTOR		//figure out what this does
_interrupt void Port_1(void)
{
	P1OUT ^= LED;				//Toggle green LED
	P1IFG &= ~BUTTON;			//Clear BUTTON interrupt flag
}