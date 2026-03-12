//rtc_defines.h
/*------------------------------------------------------------
File: rtc_defines.h
Purpose:
Contains macro definitions required for configuring and
controlling the Real-Time Clock (RTC) of LPC21xx/LPC214x
microcontrollers.

This file defines:
- System and peripheral clock values
- RTC prescaler calculation values
- RTC control register bit definitions
------------------------------------------------------------*/

#ifndef RTC_DEFINES_H
#define RTC_DEFINES_H

//------------------------------------------------------------
// System Clock and Peripheral Clock Macros
//------------------------------------------------------------
#define FOSC 12000000        // External oscillator frequency = 12 MHz
#define CCLK (5*FOSC)        // CPU clock frequency using PLL (5 × FOSC)
#define PCLK (CCLK/4)        // Peripheral clock frequency

//------------------------------------------------------------
// RTC Prescaler Values
//------------------------------------------------------------
// RTC requires a 32.768 kHz clock.
// PREINT and PREFRAC are used to derive this clock from PCLK.
#define PREINT_VAL  ((PCLK/32768)-1)                  // Integer prescaler value
#define PREFRAC_VAL (PCLK-(PREINT_VAL+1)*32768)       // Fractional prescaler value

//------------------------------------------------------------
// RTC Control Register (CCR) Bit Definitions
//------------------------------------------------------------
#define RTC_ENABLE  (1<<0)   // Bit 0: Enable RTC counter
#define RTC_RESET   (1<<1)   // Bit 1: Reset RTC counter and prescaler
#define RTC_CLKSRC  (1<<4)   // Bit 4: Select RTC clock source (for LPC2148)

//------------------------------------------------------------
// Uncomment this macro if using LPC2148 device
// This enables alternate RTC clock source configuration
//------------------------------------------------------------
//#define _LPC2148

#endif
