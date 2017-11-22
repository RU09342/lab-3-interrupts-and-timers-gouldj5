# LAB 3 - TIMER A Blink
#### Joshua Gould
##### Created - 10-13-2017
##### Updated - 10-14-2017

## Library Used
msp430.h - default library including extra work

## Dependencies
* MSP430 Development board
* CCS coding software

## Set Requirements
"Using the TIMER module instead of a software loop, control the speed of two LEDS blinking on your development boards. Experiment with the different counting modes available as well as the effect of the pre-dividers. Why would you ever want to use a pre-divider? What about the Capture and Compare registers? Your code should include a function (if you want, place it in its own .c and .h files) which can convert a desired Hz into the proper values required to operate the TIMER modules."

#### Tasks
* [x] Control the speed of two LEDS blinking on your development boards
* [x] Use the TIMER module
* [x] Extra Work

## Compatibility
* MSP430F5529
* MSP430FR2311
* MSP430FR6989
* MSP430FR5594
* MSP430G2553

# Functionality Description
Control the speed of two LEDS blinking on your development boards using the TIMER modules
### Detailed Description

* 

### Example Code
```C

```

# Extra Work Description

#### Title

#### Example Code
```C

```
# 
The TIMER peripherals can be used in many situations thanks to it flexibility in features. For this lab, you will be only scratching the surface as to what this peripheral can do. 

## Up, Down, Continuous 
There are a few different ways that the timer module can count. For starters, one of the easiest to initialize is Continuous counting where in the TIMER module will alert you when its own counting register overflows. Up mode allows you to utilize a Capture/Compare register to have the counter stop at a particular count and then start back over again. You can also set the TIMER to Up/Down mode where upon hitting a counter or the overflow, instead of setting the counter back to zero, it will count back down to zero. 

## Task

### Extra Work

#### Thinking with HALs
Using a "config.h" file with IFDEF statements, the file can check to see what processor is on board and initialize particular registers based on that.
####Code
```C

```