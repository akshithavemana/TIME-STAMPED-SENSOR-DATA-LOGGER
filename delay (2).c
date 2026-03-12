//delay.c
/*------------------------------------------------------------
File: delay.c
Purpose:
Provides software delay functions for LPC214x ARM7
microcontroller using simple loop-based timing.

These delay routines are useful for:
- Creating small time delays
- LCD timing requirements
- ADC stabilization delays
- Keypad debounce delays

NOTE:
These delays are approximate and depend on CPU clock
frequency and compiler optimization.
------------------------------------------------------------*/

#include "types.h"   // User-defined data types

//------------------------------------------------------------
// Function: delay_us
// Purpose : Generate a microsecond-level delay
// Parameter:
//   tdly -> Delay time in microseconds
//
// Working:
// - Multiplies delay count based on CPU clock (12 MHz)
// - Uses a simple decrementing loop
//------------------------------------------------------------
void delay_us(unsigned int tdly)
{
        tdly *= 12;          // Adjust loop count for 1 µs delay
        while(tdly--);       // Busy-wait loop
}

//------------------------------------------------------------
// Function: delay_ms
// Purpose : Generate a millisecond-level delay
// Parameter:
//   tdly -> Delay time in milliseconds
//
// Working:
// - Multiplies delay count based on CPU clock
// - Calls a busy-wait loop for approximate timing
//------------------------------------------------------------
void delay_ms(unsigned int tdly)
{
        tdly *= 12000;       // Adjust loop count for 1 ms delay
        while(tdly--);       // Busy-wait loop
}

//------------------------------------------------------------
// Function: delay_s
// Purpose : Generate a second-level delay
// Parameter:
//   tdly -> Delay time in seconds
//
// Working:
// - Multiplies delay count based on CPU clock
// - Uses a busy-wait loop (not CPU efficient)
//------------------------------------------------------------
void delay_s(unsigned int tdly)
{
        tdly *= 12000000;    // Adjust loop count for 1 second delay
        while(tdly--);       // Busy-wait loop
}
