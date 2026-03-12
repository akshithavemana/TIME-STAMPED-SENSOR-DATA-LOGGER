//KeyPdDefines.h
/*------------------------------------------------------------
File: KeyPdDefines.h
Purpose:
Definitions for 4x4 matrix keypad interface
used with LPC21xx / LPC214x microcontrollers.

This file provides:
- Row and column GPIO pin definitions
- Lookup table (LUT) for keypad key values
------------------------------------------------------------*/

#include <LPC21xx.h>
#include "types.h"

//------------------------------------------------------------
// GPIO Pin Assignments for Keypad
// Port 1 is used for keypad interfacing
//------------------------------------------------------------

// Row pins (configured as OUTPUT)
#define R0 16     // P1.16
#define R1 17     // P1.17
#define R2 18     // P1.18
#define R3 19     // P1.19

// Column pins (configured as INPUT)
#define C0 20     // P1.20
#define C1 21     // P1.21
#define C2 22     // P1.22
#define C3 23     // P1.23

//------------------------------------------------------------
// Keypad Lookup Table (LUT)
// Maps row–column combination to key values
//
// Example:
// Row 0, Col 0 -> 0
// Row 0, Col 1 -> 1
// ...
// Row 3, Col 3 -> 15
//------------------------------------------------------------
u8 LUT[][4] =
{
    { 0,  1,  2,  3},
    { 4,  5,  6,  7},
    { 8,  9, 10, 11},
    {12, 13, 14, 15}
};
