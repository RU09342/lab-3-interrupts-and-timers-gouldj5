#include <msp430.h>
/*
MSP430FR2311
Button Interrupt
*/
#define BUTTON BIT1		//P1.1 BUTTON defined
#define LED   BIT0		//P1.0 LED green defined

#define BTNREN P1REN
#define BTNOUT P1OUT
#define BTNIES P1IES
#define BTNIE P1IE
#define BTNIFG P1IFG

void main(void) {
	WDTCTL = WDTPW | WDTHOLD;	//stop watchdog timer

	P1DIR |= LED;				//set LED pin to output
	P1OUT &= ~LED;

	BTNREN |= BUTTON;			//Enable pull-resistor
	BTNOUT |= BUTTON;			//Make pull-resistor a pull-up
	BTNIES &= ~BUTTON;			//Rising edge interrupt
	BTNIE |= BUTTON;		 		//Enable interrupt on BUTTON
	BTNIFG |= BUTTON;			//Clear interrupt


	__bis_SR_register(LPM4_bits + GIE);                 // Enable interrupts globally

}

// Port 1 interrupt service routine
#pragma vector=PORT5_VECTOR
__interrupt void Port_5(void)
{
		P1OUT ^= LED;				//Toggle green LED
		BTNIFG &= ~BUTTON;			//Clear BUTTON interrupt flag
}