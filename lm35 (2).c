//lm35.c
/*------------------------------------------------------------
File: lm35.c
Purpose:
Source file for interfacing LM35 temperature sensor with
LPC214x ARM7 microcontroller using ADC.

This file provides:
- Functions to read temperature from LM35
- Temperature output in Celsius or Fahrenheit
------------------------------------------------------------*/

#include "types.h"         // User-defined data types
#include "adc.h"          // ADC driver functions
#include "adc_defines.h"   // ADC channel definitions

/*------------------------------------------------------------
Function: Read_LM35
Purpose :
Reads temperature from LM35 sensor using single-ended ADC.

Parameter:
tType : Temperature type
        'C' -> Celsius
        'F' -> Fahrenheit

Return:
Temperature value as floating-point number
------------------------------------------------------------*/
f32 Read_LM35(u8 tType)
{
        u32 adcDVal;       // Raw ADC digital value
        f32 eAR, tDeg;     // eAR: Equivalent analog reading, tDeg: temperature

        //------------------------------------------------------
        // Read ADC channel connected to LM35
        //------------------------------------------------------
        Read_ADC(CH1, &eAR, &adcDVal);

        //------------------------------------------------------
        // Convert voltage to temperature (10 mV per °C)
        //------------------------------------------------------
        tDeg = eAR * 100;

        //------------------------------------------------------
        // Temperature format selection
        //------------------------------------------------------
        if (tType == 'C');
        else if (tType == 'F')
                tDeg = ((tDeg * (9 / 5.0)) + 32);

        return tDeg;       // Return temperature value
}

/*------------------------------------------------------------
Function: Read_LM35_NP
Purpose :
Reads temperature from LM35 using differential (non-polarized)
ADC input configuration.

Parameter:
tType : Temperature type
        'C' -> Celsius
        'F' -> Fahrenheit

Return:
Temperature value as floating-point number
------------------------------------------------------------*/
f32 Read_LM35_NP(u8 tType)
{
        u32 adcDVal1, adcDVal2;   // Raw ADC digital values
        f32 eAR1, eAR2, tDeg;     // Analog readings and temperature

        //------------------------------------------------------
        // Read ADC channels for differential measurement
        //------------------------------------------------------
        Read_ADC(CH0, &eAR1, &adcDVal1);
        Read_ADC(CH1, &eAR2, &adcDVal2);

        //------------------------------------------------------
        // Calculate temperature from voltage difference
        //------------------------------------------------------
        tDeg = (eAR1 - eAR2) * 100;

        //------------------------------------------------------
        // Temperature format selection
        //------------------------------------------------------
        if (tType == 'C');
        else if (tType == 'F')
                tDeg = ((tDeg * (9 / 5.0)) + 32);

        return tDeg;       // Return temperature value
}
