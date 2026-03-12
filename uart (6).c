//uart.c
/*------------------------------------------------------------
File: uart.c
Purpose:
Source file for UART0 communication on LPC21xx/LPC214x
ARM7 microcontroller.

This file provides:
- UART initialization
- Character, string, integer, and float transmission
- Display of date and time via serial terminal
------------------------------------------------------------*/

#include <LPC21xx.h>     // LPC21xx/LPC214x register definitions
#include "defines.h"     // Bit manipulation macros
#include "types.h"       // User-defined data types

//------------------------------------------------------------
// Array holding abbreviated names of days (for UART display)
//------------------------------------------------------------
char week1[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};

/*------------------------------------------------------------
Function: InitUART
Purpose :
Initializes UART0 for serial communication.

Configuration:
- TXD0 on P0.0
- RXD0 on P0.1
- 8-bit data, 1 stop bit
- Baud rate configured using DLL and DLM
------------------------------------------------------------*/
void InitUART(void)
{
        //----------------------------------------------------------
        // Select UART function for P0.0 (TXD0) and P0.1 (RXD0)
        //----------------------------------------------------------
        PINSEL0 |= 0x00000001;
        //CfgPinFunc(0,0,1);   // P0.0 for TXD0
        //CfgPinFunc(0,1,1);   // P0.1 for RXD0

        //----------------------------------------------------------
        // Line Control Register configuration
        //----------------------------------------------------------
        U0LCR = 0x03;          // 8-bit word length, 1 stop bit
        U0LCR |= 1 << 7;       // Enable DLAB to access baud rate registers

        //----------------------------------------------------------
        // Baud rate configuration (example: 9600 bps @ 15 MHz PCLK)
        //----------------------------------------------------------
        U0DLL = 97;
        U0DLM = 0;

        //----------------------------------------------------------
        // Disable DLAB after baud rate setup
        //----------------------------------------------------------
        U0LCR &= ~(1 << 7);
}

/*------------------------------------------------------------
Function: UARTRxChar
Purpose :
Receives a single character from UART.
------------------------------------------------------------*/
s8 UARTRxChar(void)
{
        //----------------------------------------------------------
        // Wait until data is available in receiver buffer
        //----------------------------------------------------------
        while (!READBIT(U0LSR, 0));

        return (U0RBR);        // Return received character
}

/*------------------------------------------------------------
Function: UARTTxChar
Purpose :
Transmits a single character via UART.
------------------------------------------------------------*/
void UARTTxChar(s8 ch)
{
        U0THR = ch;            // Load character into transmit register

        //----------------------------------------------------------
        // Wait until transmission is complete
        //----------------------------------------------------------
        while (!READBIT(U0LSR, 6));
}

/*------------------------------------------------------------
Function: UARTTxStr
Purpose :
Transmits a null-terminated string via UART.
------------------------------------------------------------*/
void UARTTxStr(s8 *ptr)
{
        while (*ptr)
                UARTTxChar(*ptr++);
}

/*------------------------------------------------------------
Function: UARTTxU32
Purpose :
Transmits an unsigned 32-bit integer via UART.
------------------------------------------------------------*/
void UARTTxU32(u32 num)
{
        u8 a[10];             // Buffer to store digits
        s8 i = 0;

        //----------------------------------------------------------
        // Handle zero case
        //----------------------------------------------------------
        if (num == 0)
                UARTTxChar('0');
        else
        {
                //------------------------------------------------------
                // Convert integer to ASCII characters
                //------------------------------------------------------
                while (num > 0)
                {
                        a[i++] = num % 10 + 48;
                        num = num / 10;
                }

                //------------------------------------------------------
                // Transmit digits in correct order
                //------------------------------------------------------
                for (--i; i >= 0; i--)
                        UARTTxChar(a[i]);
        }
}

/*------------------------------------------------------------
Function: UARTTxF32
Purpose :
Transmits a floating-point number via UART.
------------------------------------------------------------*/
void UARTTxF32(f32 fnum)
{
        u32 num, i;

        //----------------------------------------------------------
        // Handle negative numbers
        //----------------------------------------------------------
        if (fnum < 0)
        {
                UARTTxChar('-');
                fnum = -fnum;
        }

        //----------------------------------------------------------
        // Transmit integer part
        //----------------------------------------------------------
        num = fnum;
        UARTTxU32(num);
        UARTTxChar('.');

        //----------------------------------------------------------
        // Transmit fractional part (6 decimal places)
        //----------------------------------------------------------
        for (i = 0; i < 6; i++)
        {
                fnum = (fnum - num) * 10;
                num = fnum;
                UARTTxChar(num + 48);
        }
}

/*------------------------------------------------------------
Function: DisplayUARTDate
Purpose :
Displays date in DD/MM/YYYY format via UART.
------------------------------------------------------------*/
void DisplayUARTDate(u32 date, u32 month, u32 year)
{
        UARTTxChar((date / 10) + 48);
        UARTTxChar((date % 10) + 48);
        UARTTxChar('/');
        UARTTxChar((month / 10) + 48);
        UARTTxChar((month % 10) + 48);
        UARTTxChar('/');
        UARTTxU32(year);
}

/*------------------------------------------------------------
Function: DisplayUARTTime
Purpose :
Displays time in HH:MM:SS format via UART.
------------------------------------------------------------*/
void DisplayUARTTime(u32 hour, u32 minute, u32 second)
{
        UARTTxChar((hour / 10) + 48);
        UARTTxChar((hour % 10) + 48);
        UARTTxChar(':');
        UARTTxChar((minute / 10) + 48);
        UARTTxChar((minute % 10) + 48);
        UARTTxChar(':');
        UARTTxChar((second / 10) + 48);
        UARTTxChar((second % 10) + 48);
        UARTTxChar(' ');
}
