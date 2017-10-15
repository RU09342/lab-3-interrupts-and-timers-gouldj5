# Lab 3 - Button Based Delay
#### Joshua Gould
##### Created - 10-14-2017
##### Updated - 10-14-2017

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
* [ ] Button works with timer to change speed
* [ ] Extra Work

## Compatibility
* MSP430F5529
* MSP430FR2311
* MSP430FR6989
* MSP430FR5594
* MSP430G2553

# Functionality Description

### Detailed Description

* 

### Example Code
```C

```

# Extra Work Description

#### Title
### Reset Button
(Works)
Reset Button sets the blink back to 10Hz for all processors

### Button Based Hertz
Most likely using two buttons, what if instead of making a delay loop based on the time, the user could instead enter a mode where the number of times they pressed the button would become the number in Hz of the blinking rate? How do you think you would implement that with just one button?

#### Example Code
```C

```

## Current Compatability 
MSP430G2553


### Extra Work
