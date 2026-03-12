//adc_defines.h
/*------------------------------------------------------------
File: adc_defines.h
Purpose:
Contains macros and definitions for ADC configuration
for LPC21xx microcontroller.

This file defines:
- System and peripheral clocks
- ADC control register bit positions
- ADC channel pin selection
- ADC channel numbers
------------------------------------------------------------*/

//------------------------------------------------------------
// System Clock and Peripheral Clock Definitions
//------------------------------------------------------------
#define FOSC 12000000          // External crystal frequency = 12 MHz
#define CCLK (FOSC*5)          // CPU clock = FOSC * 5 (PLL multiplier)
#define PCLK (CCLK/4)          // Peripheral clock = CCLK / 4
#define ADCCLK 3000000         // Desired ADC clock frequency = 3 MHz
#define CLKDIV ((PCLK/ADCCLK)-1)  // ADC clock divider (for ADCR register)

//------------------------------------------------------------
// ADCR (ADC Control Register) Bit Positions
//------------------------------------------------------------
#define CLKDIV_BITS        8   // Bits 8–15: Clock divider value
#define PDN_BIT            21  // Bit 21: ADC Power Down control (1 = ADC enabled)
#define ADC_CONV_START_BIT 24  // Bit 24: Start conversion control

//------------------------------------------------------------
// ADDR (ADC Data Register) Bit Positions
//------------------------------------------------------------
#define DIGITAL_DATA_BITS 6    // Bits 6–15: 10-bit ADC result
#define DONE_BIT          31   // Bit 31: Conversion done flag

//------------------------------------------------------------
// ADC Pin Selection (PINSEL1 configuration for AIN0–AIN3)
// P0.27 ? AIN0, P0.28 ? AIN1, P0.29 ? AIN2, P0.30 ? AIN3
//------------------------------------------------------------
#define AIN0_PIN_0_27 0x00400000
#define AIN1_PIN_0_28 0x01000000
#define AIN2_PIN_0_29 0x04000000
#define AIN3_PIN_0_30 0x10000000

//------------------------------------------------------------
// ADC Channel Numbers
//------------------------------------------------------------
#define CH0 0
#define CH1 1
#define CH2 2
#define CH3 3

//------------------------------------------------------------
// Note:
// Additional ADC channels and configurations can be added
// here as required for other analog inputs.
// Example: #define AIN4_PIN_0_31 0x40000000
//------------------------------------------------------------
