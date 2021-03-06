#include <msp430.h>
/*
MSP430FR6989
Button Interrupt
*/
#define BUTTON BIT1				//P1.1 BUTTON defined
#define LED   BIT0				//P1.0 LED green defined

void main(void) {
	WDTCTL = WDTPW | WDTHOLD;	//stop watchdog timer

	P1DIR |= LED;				//set LED pin to output
	P1DIR &= ~BUTTON;			//set button to input
	P1REN |= BUTTON;			//Enable pull-resistor
	P1OUT |= BUTTON;			//Make pull-resistor a pull-up

	P1IES &= ~BUTTON;			//Rising edge interrupt
	P1IE |= BUTTON;		 		//Enable interrupt on BUTTON

	PM5CTL0 &= ~LOCKLPM5;		//disable high impedence

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