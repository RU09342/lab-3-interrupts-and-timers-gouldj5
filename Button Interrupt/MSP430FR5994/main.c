#include <msp430.h>
/*
MSP4305994
Button Interrupt
*/
#define BUTTON BIT6		//P1.6 BUTTON defined
#define LED   BIT0		//P1.0 LED green defined

#define BTNREN P5REN
#define BTNOUT P5OUT
#define BTNIES P5IES
#define BTNIE P5IE
#define BTNIFG P5IFG

void main(void) {
	WDTCTL = WDTPW | WDTHOLD;	//stop watchdog timer

	P1DIR |= LED;				//set LED pin to output
	P1OUT &= ~LED;

	BTNREN |= BUTTON;			//Enable pull-resistor
	BTNOUT |= BUTTON;			//Make pull-resistor a pull-up
	BTNIES &= ~BUTTON;			//Rising edge interrupt
	BTNIE |= BUTTON;		 		//Enable interrupt on BUTTON
	BTNIFG |= BUTTON;			//Clear interrupt

	PM5CTL0 &= ~LOCKLPM5;		//global interrupt

	__bis_SR_register(GIE);                 // Enable interrupts globally

}

// Port 1 interrupt service routine
#pragma vector=PORT5_VECTOR
__interrupt void Port_5(void)
{
	if (!(P5IN & BUTTON))		//if button pressed
	{
		P1OUT ^= LED;				//Toggle green LED
		BTNIFG &= ~BUTTON;			//Clear BUTTON interrupt flag
	}
}