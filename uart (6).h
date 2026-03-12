/*------------------------------------------------------------
File: uart.h
Purpose:
Header file for UART (Universal Asynchronous Receiver Transmitter)
communication functions used with LPC21xx / LPC214x microcontrollers.

This file provides:
- UART initialization
- Character and string transmission functions
- Number (integer and float) transmission functions
- Date and time display utilities over UART
------------------------------------------------------------*/

#ifndef __UART_H__
#define __UART_H__

#include "types.h"

//------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------

/*------------------------------------------------------------
Function: InitUART
Purpose : Initializes UART peripheral
          - Configures baud rate
          - Sets data frame format (8N1 typically)
          - Enables transmitter
------------------------------------------------------------*/
void InitUART(void);

/*------------------------------------------------------------
Function: UARTTxChar
Purpose : Transmits a single character via UART
Input   : s8 - character to transmit
------------------------------------------------------------*/
void UARTTxChar(s8);

/*------------------------------------------------------------
Function: UARTTxStr
Purpose : Transmits a null-terminated string via UART
Input   : s8* - pointer to string
------------------------------------------------------------*/
void UARTTxStr(s8 *);

/*------------------------------------------------------------
Function: UARTTxU32
Purpose : Transmits a 32-bit unsigned integer in ASCII format
Input   : u32 - unsigned 32-bit integer
------------------------------------------------------------*/
void UARTTxU32(u32);

/*------------------------------------------------------------
Function: UARTTxF32
Purpose : Transmits a 32-bit floating-point number
          (Converted to ASCII before transmission)
Input   : f32 - floating-point value
------------------------------------------------------------*/
void UARTTxF32(f32);

/*------------------------------------------------------------
Function: DisplayUARTDate
Purpose : Displays formatted date over UART
Format  : DD/MM/YYYY (or implementation dependent)
Input   : date  - day
          month - month
          year  - year
------------------------------------------------------------*/
void DisplayUARTDate(u32 date, u32 month, u32 year);

/*------------------------------------------------------------
Function: DisplayUARTTime
Purpose : Displays formatted time over UART
Format  : HH:MM:SS
Input   : hour   - hours
          minute - minutes
          second - seconds
------------------------------------------------------------*/
void DisplayUARTTime(u32 hour, u32 minute, u32 second);

/*------------------------------------------------------------
Function: DisplayUARTDay
Purpose : Displays day of week over UART
Input   : dow - day of week (0–6 or 1–7 depending on implementation)
------------------------------------------------------------*/
void DisplayUARTDay(u32 dow);

/*------------------------------------------------------------
Function: setUART
Purpose : Configures UART settings dynamically
          (Used for runtime configuration if required)
------------------------------------------------------------*/
void setUART(void);

/*------------------------------------------------------------
Function: DisplayUART
Purpose : General UART display handler function
          (May combine multiple display functions internally)
------------------------------------------------------------*/
void DisplayUART(void);

#endif
