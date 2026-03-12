/*------------------------------------------------------------
File: adc.h
Purpose:
Header file for ADC (Analog-to-Digital Converter)
functions used with LPC21xx / LPC214x microcontrollers.

This file provides:
- ADC initialization
- ADC channel reading function
------------------------------------------------------------*/

#ifndef __ADC_H__
#define __ADC_H__

#include "types.h"

//------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------

/*------------------------------------------------------------
Function: Init_ADC
Purpose : Initializes the ADC peripheral for a given channel
          - Configures ADC pin as analog input
          - Sets ADC clock
          - Enables selected ADC channel
Input   : chNo - ADC channel number (e.g., 0 to 7 depending on MCU)
------------------------------------------------------------*/
void Init_ADC(u32 chNo);

/*------------------------------------------------------------
Function: Read_ADC
Purpose : Reads analog value from specified ADC channel

Process :
          - Starts ADC conversion
          - Waits for conversion completion
          - Reads digital ADC result
          - Converts digital value to equivalent analog voltage

Inputs  :
          chNo    - ADC channel number
          eAR     - Pointer to store equivalent analog result (float)
          adcDVal - Pointer to store raw ADC digital value (integer)

Notes   :
          Digital value range depends on ADC resolution
          (e.g., 10-bit ADC ? 0 to 1023)
------------------------------------------------------------*/
void Read_ADC(u32 chNo, f32 *eAR, u32 *adcDVal);

#endif
