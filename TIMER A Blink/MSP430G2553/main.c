#include <msp430.h>

#define LED0 BIT0
#define LED1 BIT0

void timer(int capture);

unsigned int timerCount = 0;
void main(void)
{
	WDTCTL = WDTPW + WDTHOLD; //stop watchdog
	P1DIR |= (LED0 + LED1); //set  P1.0 & 1.6 to output
	P1OUT &= ~(LED0 + LED1); //start LEDs off

	timer(20); //initialize timer at 10Hz 

	_enable_interrupt();

	_bis_SR_register(LPM0 + GIE); //LPM0 with interrupts
}
void timer(int hertz) //seconds = 1/HZ= 1/10
{
	CCTL0 = CCIE;
	TACTL = TASSEL_2 + MC_1 + ID_3; //SMCLK
									//UPMODE
									//SMCLK/8 = 1MHZ/8 = 125kHZ
	int capture = (125000) / hertz;
	TTACR0 = capture; // (1M/8)/(12500) =10Hz
}

//TimerA0 interrupt sequence
#pragma vector=Timer_A0_VECTOR
_interrupt void Timer0_A0(void)
{
	if (timerCount >= 100)
	{
		P1OUT ^= (LED0 + LED1); //turn on LED
		timerCount = 0; //Reset
	}
	else timerCount++; //increment until 10s
}