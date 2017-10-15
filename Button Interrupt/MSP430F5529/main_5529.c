#include <msp430.h>
/*
MSP430FR5529
Button Interrupt
*/
#define BUTTON BIT1		//P1.1 BUTTON defined
#define LED   BIT0		//P1.0 LED green defined
#define LED2  BIT7

#define BTNREN P2REN	
#define BTNOUT P2OUT
#define BTNIES P2IES
#define BTNIE P2IE
#define BTNIFG P2IFG

void main(void) {
	WDTCTL = WDTPW | WDTHOLD;	//stop watchdog timer

	P1DIR |= LED;				//set LED pin to output
	P4DIR |= LED2;

	P2DIR &= ~BUTTON;
	P1OUT &= ~LED;

	BTNREN |= BUTTON;			//Enable pull-resistor
	BTNOUT |= BUTTON;			//Make pull-resistor a pull-up
	BTNIES &= ~BUTTON;			//Rising edge interrupt
	BTNIE |= BUTTON;		 		//Enable interrupt on BUTTON
	BTNIFG |= BUTTON;			//Clear interrupt

	PM5CTL0 &= ~LOCKLPM5;		//disable high impedence

	__bis_SR_register(GIE);                 // Enable interrupts globally

}

// Port 2 ISR
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
	if (!(P2IN & BUTTON))		//if button pressed
	{	
		P1OUT ^= LED;			//Toggle green LED
		BTNIFG &= ~BUTTON;		//Clear BUTTON interrupt flag
	}
	else
	{
		P4OUT ^= LED2;			//toggles LED2
		BTNIES |= BUTTON;		//set fall edge
	}
	BTNIFG &= ~BUTTON;
}