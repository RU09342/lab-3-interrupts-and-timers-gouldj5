# Lab 3 - Button Based Delay
#### Joshua Gould
##### Created - 10-14-2017
##### Updated - 10-16-2017

## Library Used
msp430.h - default library

## Dependencies
* MSP430 Development board
* CCS coding software

## Set Requirements
"Setup your microcontroller to initially blink and LED at a rate of 10Hz upon restarting or powering up. Then utilizing one of the buttons on board, a user should be able to set the delay or blinking rate of the LED by holding down a button. The duration in which the button is depressed should then become the new rate at which the LED blinks. As previously stated, you most likely will want to take advantage of the fact that TIMER modules exist and see if you can let them do a bulk of the work for you."

#### Tasks
* [x] Start blink at 10Hz
* [x] Button controlled speed change
* [x] Button works with timer to change speed
* [ ] Extra Work

## Compatibility
* MSP430F5529
* MSP430FR2311
* MSP430FR6989
* MSP430FR5594
* MSP430G2553

The pin assignments on each board can be different. Certain boards with FR require high impedence on a pin to be disabled. Certain boards use a different timer.

# Functionality Description
The LED will blink at a rate of 10Hz upon restarting or powering up. 
Then utilizing one of the buttons on board, a user can set the delay or blinking rate of the LED by holding down a button. 
The duration in which the button is depressed should then become the new rate at which the LED blinks.
### Detailed Description
* When the timer reaches a sepecifed value, an interrupt occurs
* TA0CCR0 value toggles the LED
* When the button is released, another interrupt fires off and setting the TA0CCR0 value to a count.


### Example Code
```C
#include <msp430.h>
/*
MSP430G2553
Button Based Delay
*/
#define LED0 BIT0		// definitions of LED pins
#define LED1 BIT6
#define LED0DIR P1DIR
#define LED1DIR P1DIR
#define LED0OUT P1OUT
#define LED1OUT P1OUT

#define speed1 1		//Speed definitions
#define speed2 3
#define speed3 5
#define speed4 10
#define speed5 20
#define speed6 50

#define BUTTON BIT3		// definitions of BUTTON pins
#define BTNREN P1REN
#define BTNOUT P1OUT
#define BTNIES P1IES
#define BTNIE P1IE
#define BTNIFG P1IFG

unsigned int timerCount = 1; //check button to change speed
unsigned int ledCount = 1; //blink with timer
unsigned int ledSpeed = 1; //keep track of LED speed
unsigned int enabled = 0;  //button interface
unsigned int hzSpeed = speed1;  //hz speed track

void initTimer(int capture);
void speedSet(int speed);

void main(void)
{
	WDTCTL = WDTPW + WDTHOLD; // Stop watchdog
	LED0DIR |= (LED0);                // configure P1.0 as output
	LED1DIR |= (LED1);                // configure P4.7 as output
	LED0OUT &= ~(LED0);               // reset the LEDs
	LED1OUT &= ~(LED1);               // reset the LEDs

	BTNREN |= BUTTON;                  // puller-resistor on the button pin P1.1
	BTNOUT |= BUTTON;                  // writes resistor to pullup
	BTNIES |= BUTTON;                  // triggers when you press the button, "~BIT1" for when release
	BTNIE |= BUTTON;                   // enables selector-mask for generating interrupts on the pin
	BTNIFG &= BUTTON;

	initTimer(10);					  // Initialize timer at 10Hz 

	__enable_interrupt();

	__bis_SR_register(LPM0 + GIE); // LPM0 with interrupts enabled
}

void initTimer(int hertz) //hertz pertains to clock time
{
	TA0CCTL0 = CCIE;				// CCR0 interrupt enabled
	TACTL = TASSEL_2 + MC_1 + ID_3; // SMCLK = 1MHZ -> TASSEL_2
									// UPMODE -> Mc_1
									// ID_3 devides SMCLK by 8 I_(11_2)
	int capture = (125000) / hertz;  //manage frequency
	TACCR0 = capture; // (1000000/8)/(12500) = 10 Hz = 0.1 seconds
					  // CLK = 1MHZ/8 = 12.5kHz
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) // function called when the port is interrupted (button pressed)
{
	// Button to change the speed of the blinking LED
	enabled ^= 0x01; // Toggle enable for checking to change blink frequency
	BTNIFG &= ~BUTTON; // Reset the interupt flag
	BTNIES ^= BUTTON; // This will trigger the edge so when it is released it will toggle the enable again
}
// TimerA0 interrupt sequence
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0(void)
{
	// Timer portion to increase the speed
	if (timerCount >= 10) // 0.1 seconds 10 times, called every 1s
	{
		LED1OUT &= ~(LED1); // Turn off LED used to show speed changing
		if (enabled > 0)
		{
			if (ledSpeed >= 10) ledSpeed = 1; // reset ledSpeed at 10
			else ledSpeed++; // Increment the speed setting each time the button is pressed
			LED1OUT |= (LED1); // Show LED to indicate speed has changed
			speedSet(ledSpeed);
		}
		timerCount = 1; // Reset the counter variable
	}
	else timerCount++; // Increment the counter variable until 10s

	if (ledCount >= hzSpeed)
	{
		LED0OUT ^= (LED0); // Toggle LED to blink
		ledCount = 1; // Reset the counter
	}
	else ledCount++; // Increment the counter until it reaches threshold
}
void speedSet(int speed) // Sets the hzSpeed to match constant definitions
{						// could do a case statement here
	if (speed == 1) hzSpeed = speed1;
	else if (speed == 2) hzSpeed = speed2;
	else if (speed == 3) hzSpeed = speed3;
	else if (speed == 4) hzSpeed = speed4;
	else if (speed == 5) hzSpeed = speed5;
	else if (speed == 6) hzSpeed = speed6;
	else hzSpeed = speed1;
}
```