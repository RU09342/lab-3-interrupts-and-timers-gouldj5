#include <msp430.h>
/*
MSP430G2553
Timer A Blink
*/
#define LED0 BIT0		// definitions of pins
#define LED1 BIT7

void initTimer(int capture); //function calling capture

unsigned int timerCount = 0; //check unsigned
void main(void)
{
	WDTCTL = WDTPW + WDTHOLD; // Stop watchdog
	P1DIR |= LED0; // Set P1.0 & P1.6 to output direction
	P1OUT &= ~LED0; // Start LED off
	P4DIR |= LED1; // Set P4.7 to output direction
	P4OUT &= ~LED1; // Start LED off

	initTimer(20); // Initialize timer at 10Hz or 0.1s

	__enable_interrupt();
	PM5CTL0 &= ~LOCKLPM5;		//disable high impedence
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
		P1OUT ^= LED0; //toggle on LED
		P4OUT ^= LED1;
		timerCount = 0; //Reset timer
	}
	else timerCount++; //increment until ~2.5s
}