//delay.h
/*------------------------------------------------------------
File: delay.h
Purpose:
Header file for delay functions for LPC21xx microcontroller.

This file provides:
- Microsecond, millisecond, and second delays
- Functions typically implemented using Timer0 or software loops
------------------------------------------------------------*/

#include "types.h"   // User-defined data types

//------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------

//------------------------------------------------------------
// Function: delay_us
// Purpose : Delay for a specified number of microseconds
// Parameter: u32 -> Number of microseconds to delay
//------------------------------------------------------------
void delay_us(u32);

//------------------------------------------------------------
// Function: delay_ms
// Purpose : Delay for a specified number of milliseconds
// Parameter: u32 -> Number of milliseconds to delay
//------------------------------------------------------------
void delay_ms(u32);

//------------------------------------------------------------
// Function: delay_s
// Purpose : Delay for a specified number of seconds
// Parameter: u32 -> Number of seconds to delay
//------------------------------------------------------------
void delay_s(u32);
