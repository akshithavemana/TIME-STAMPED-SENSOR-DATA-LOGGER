//lm35.h
/*------------------------------------------------------------
File: lm35.h
Purpose:
Header file for LM35 temperature sensor interface.

This file contains:
- Function prototypes for reading temperature from LM35
- Supports Celsius and Fahrenheit output formats
------------------------------------------------------------*/

#include "types.h"   // User-defined data type definitions

//------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------

//------------------------------------------------------------
// Function: Read_LM35
// Purpose : Read temperature from LM35 using ADC
//           Returns temperature in Celsius or Fahrenheit
//------------------------------------------------------------
f32 Read_LM35(u8 tType);

//------------------------------------------------------------
// Function: Read_LM35_NP
// Purpose : Read temperature using differential ADC method
//           (non-polarized measurement)
//------------------------------------------------------------
f32 Read_LM35_NP(u8 tType);
