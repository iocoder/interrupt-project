# interrupt-project

AVR exercise involving buttons, timers, leds, and interrupts.

## Problem Statement

Given an ATMEGA32 chip with a push button connected to pin PD2 (INT0 pin), and 4 LEDs
connected to PA0-PA3 pins. Design a program where LED outputs will keep toggling between
ON and OFF states until the push button is pressed.

When the push button is pressed, the LEDs state should immediately change to ON, and
they should be kept in ON state (no toggling) until the push button is released. When
the push button is released, the LEDs will keep toggling again.

It is required to handle button input using INT0, and to handle LED toggling
using a timer (ATMEGA32's 16-bit timer). In the toggling state (button released),
LEDs would toggle every 1s.

## Objectives

As you can see, the solution involves the use of two interrupts, and the actions taken
by the interrupt handlers depend on both the timer and the button.

I thought that this is a good example to show how modular firmware design will solve
the problem very easily. Each component (timer, button, and LEDs) is implemented
in a separate source file, which provides a standard interface for all components:
initialize(); loop(); and status();

The main program would initialize all the drivers in its setup(), then keeps calling
the loop() function of each driver (to sense the changes). The ISRs of the drivers
would simply set a flag that indicates that a change has happened, and the loop()
function would call external handler routine (callback function).

The main loop uses initialize() to set the callback functions of the button and the 
timer. Every 1s, timer's callback function will be called (without interrupt context),
and whenever the button is pressed or released, its callback function will be called
as well.

Using this design, we abstract the implementation of the drivers from the main problem.
The button driver, for example, is only responsible for interfacing the button and
calling the callback function in the right time (i.e. on button status change).
The implementation of the callback functions themselves is the responsibility of
the main file (main.c), which is responsible for changing the status of the LEDs 
to the correct new state when a callback function is called.

The button driver never changes LED status and never calls any LED/timer functions.
Every driver is isolated and just does its own job. That way, you can implement
each driver very easily, and test it to make sure it is PERFECT. Then, when you
implement the main logic, you are pretty sure that the drivers are not buggy
and you can test your logic independently.

To sum up, you have learned:
* Modular software design
* The concept of software abstraction
* Software interfaces with the concept of encapsulation
* The concept of callback functions
* Testing each component independently
* Separation between drivers and high-level logic that solves a problem

