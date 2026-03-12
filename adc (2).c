//adc.c
/*------------------------------------------------------------
File: adc.c
Purpose:
Implements Analog-to-Digital Converter (ADC) functions
for LPC21xx microcontroller.

Features:
- ADC pin configuration
- ADC initialization
- Reading ADC digital value and equivalent analog voltage
------------------------------------------------------------*/

#include <LPC21xx.h>      // LPC21xx register definitions
#include "types.h"        // User-defined data types
#include "delay.h"        // Delay routines
#include "adc_defines.h"  // ADC control macros and definitions

//------------------------------------------------------------
// Lookup table for ADC channel pin selection
// Maps ADC channel number to corresponding PINSEL1 bits
//------------------------------------------------------------
u32 adcChSel[4] = {
        AIN0_PIN_0_27,   // ADC Channel 0 on P0.27
        AIN1_PIN_0_28,   // ADC Channel 1 on P0.28
        AIN2_PIN_0_29,   // ADC Channel 2 on P0.29
        AIN3_PIN_0_30    // ADC Channel 3 on P0.30
};

/*------------------------------------------------------------
Function: Init_ADC
Purpose :
Initializes the ADC for a selected channel.

Parameter:
chNo : ADC channel number (0–3)

Operation:
- Configures corresponding pin as ADC input
- Sets ADC power and clock divider
------------------------------------------------------------*/
void Init_ADC(u32 chNo)
{
        //----------------------------------------------------------
        // Clear previous pin configuration for P0.27–P0.30
        //----------------------------------------------------------
        PINSEL1 &= ~(adcChSel[chNo]);

        //----------------------------------------------------------
        // Configure selected pin as ADC input (AIN0–AIN3)
        //----------------------------------------------------------
        PINSEL1 |= adcChSel[chNo];

        //----------------------------------------------------------
        // Configure ADC control register:
        // - Enable ADC (PDN bit)
        // - Set ADC clock divider
        //----------------------------------------------------------
        ADCR |= (1 << PDN_BIT) | (CLKDIV << CLKDIV_BITS);
}

/*------------------------------------------------------------
Function: Read_ADC
Purpose :
Reads ADC conversion result from a selected channel.

Parameters:
chNo     : ADC channel number (0–3)
eAR      : Pointer to store equivalent analog voltage
adcDVal  : Pointer to store raw digital ADC value

Operation:
- Select ADC channel
- Start ADC conversion
- Wait for conversion completion
- Read digital output and compute analog voltage
------------------------------------------------------------*/
void Read_ADC(u32 chNo, f32 *eAR, u32 *adcDVal)
{
        //----------------------------------------------------------
        // Clear any previously selected ADC channel
        //----------------------------------------------------------
        ADCR &= 0xFFFFFF00;

        //----------------------------------------------------------
        // Select required ADC channel and start conversion
        //----------------------------------------------------------
        ADCR |= ((1 << ADC_CONV_START_BIT) | (1 << chNo));

        //----------------------------------------------------------
        // Allow conversion time
        //----------------------------------------------------------
        delay_us(3);

        //----------------------------------------------------------
        // Wait until conversion is completed (DONE bit set)
        //----------------------------------------------------------
        while (((ADDR >> DONE_BIT) & 1) == 0);

        //----------------------------------------------------------
        // Stop ADC conversion
        //----------------------------------------------------------
        ADCR &= ~(1 << ADC_CONV_START_BIT);

        //----------------------------------------------------------
        // Read 10-bit ADC digital data
        //----------------------------------------------------------
        *adcDVal = ((ADDR >> DIGITAL_DATA_BITS) & 1023);

        //----------------------------------------------------------
        // Convert digital value to equivalent analog voltage
        // Assuming reference voltage = 3.3V
        //----------------------------------------------------------
        *eAR = *adcDVal * (3.3 / 1023);
}
