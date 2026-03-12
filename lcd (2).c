//lcd.c
/*------------------------------------------------------------
File: lcd.c
Purpose:
Source file for interfacing 16x2 LCD with LPC21xx/LPC214x
ARM7 microcontroller in 8-bit mode.

This file provides:
- LCD initialization
- Command and data transmission
- Display of characters, strings, numbers, and temperature
------------------------------------------------------------*/

#include <LPC21xx.h>     // LPC21xx/LPC214x register definitions
#include "delay.h"       // Delay routines
#include "lcd.h"         // LCD function prototypes
#include "types.h"       // User-defined data types
#include "defines.h"     // Bit manipulation macros
#include "lm35.h"        // LM35 temperature sensor definitions

//------------------------------------------------------------
// LCD pin configuration
//------------------------------------------------------------

// LCD data lines connected to P0.8 – P0.15 (8-bit data bus)
#define LCD_DAT 0xff     // Mask for 8 data lines

// LCD control pin definitions
#define RS 5             // Register Select pin connected to P0.8
#define RW 6             // Read/Write pin connected to P0.9
#define EN 7             // Enable pin connected to P0.10

/*------------------------------------------------------------
Function: InitLCD
Purpose :
Initializes the LCD in 8-bit mode.

This function:
- Configures GPIO pins for LCD
- Sends initialization command sequence
- Sets display and cursor configuration
------------------------------------------------------------*/
void InitLCD(void)
{
        //----------------------------------------------------------
        // Configure P0.0 – P0.10 as output pins for LCD
        //----------------------------------------------------------
        IODIR0 |= ((LCD_DAT << 8) | (1 << RS) | (1 << RW) | (1 << EN));
                 // Total mask: 0x7FF

        //----------------------------------------------------------
        // Initial power-on delay (minimum 15 ms required)
        //----------------------------------------------------------
        delay_ms(20);

        //----------------------------------------------------------
        // LCD reset and initialization sequence
        //----------------------------------------------------------
        CmdLCD(0x30);          // Function set (8-bit mode)
        delay_ms(10);          // Minimum 5 ms delay

        CmdLCD(0x30);          // Repeat function set
        delay_ms(1);           // Minimum 160 µs delay

        CmdLCD(0x30);          // Repeat function set
        delay_ms(1);           // Minimum 160 µs delay

        //----------------------------------------------------------
        // LCD configuration commands
        //----------------------------------------------------------
        CmdLCD(0x38);          // 8-bit mode, 5x7 font, 1-line display
        CmdLCD(0x10);          // Display OFF
        CmdLCD(0x01);          // Clear display
        CmdLCD(0x06);          // Cursor move direction
        CmdLCD(0x0c);          // Display ON, cursor ON with blinking
}

/*------------------------------------------------------------
Function: CmdLCD
Purpose :
Sends a command byte to the LCD.
------------------------------------------------------------*/
void CmdLCD(u8 cmd)
{
        IOCLR0 = 1 << RS;       // Clear RS (command mode)
        DispLCD(cmd);          // Send command to LCD
}

/*------------------------------------------------------------
Function: CharLCD
Purpose :
Displays a single character on LCD.
------------------------------------------------------------*/
void CharLCD(u8 dat)
{
        IOSET0 = 1 << RS;       // Set RS (data mode)
        DispLCD(dat);          // Send data to LCD
}

/*------------------------------------------------------------
Function: DispLCD
Purpose :
Transfers command or data byte to LCD hardware.
------------------------------------------------------------*/
void DispLCD(u8 val)
{
        IOCLR0 = 1 << RW;       // Clear RW (write operation)
        WRITEBYTE(IOPIN0, 8, val); // Write data to P0.8 – P0.15
        IOSET0 = 1 << EN;       // Set Enable pin
        delay_ms(2);           // Enable pulse width delay
        IOCLR0 = 1 << EN;       // Clear Enable pin
        delay_ms(5);           // Command execution delay
}

/*------------------------------------------------------------
Function: StrLCD
Purpose :
Displays a null-terminated string on LCD.
------------------------------------------------------------*/
void StrLCD(u8 *ptr)
{
        while (*ptr != '\0')
                CharLCD(*ptr++);
}

/*------------------------------------------------------------
Function: IntLCD
Purpose :
Displays a signed integer value on LCD.
------------------------------------------------------------*/
void IntLCD(s32 num)
{
        u8 a[10];              // Buffer to store digits
        s8 i = 0;

        //----------------------------------------------------------
        // Handle zero case
        //----------------------------------------------------------
        if (num == 0)
                CharLCD('0');
        else
        {
                //------------------------------------------------------
                // Handle negative numbers
                //------------------------------------------------------
                if (num < 0)
                {
                        num = -num;
                        CharLCD('-');
                }

                //------------------------------------------------------
                // Convert integer to ASCII digits
                //------------------------------------------------------
                while (num > 0)
                {
                        a[i++] = num % 10 + 48;
                        num = num / 10;
                }

                //------------------------------------------------------
                // Display digits in correct order
                //------------------------------------------------------
                for (--i; i >= 0; i--)
                        CharLCD(a[i]);
        }
}

/*------------------------------------------------------------
Function: StoreCustCharFont
Purpose :
Stores a custom character pattern in LCD CGRAM.
------------------------------------------------------------*/
void StoreCustCharFont(void)
{
        u8 i;
        u8 LUT[] = {0x00,0x00,0x04,0x0c,0x1c,0x1c,0x1c,0x00};

        for (i = 0; i < 8; i++)
                CharLCD(LUT[i]);
}

/*------------------------------------------------------------
Function: TempDisplay
Purpose :
Displays temperature value on LCD with degree symbol.
------------------------------------------------------------*/
void TempDisplay(u32 temp)
{
        CmdLCD(0x89);          // Set cursor position
        StrLCD("T:");

        CmdLCD(0x8b);
        IntLCD(temp);

        CmdLCD(0x8e);
        CharLCD(223);          // Degree symbol

        CmdLCD(0x8f);
        StrLCD("c");
}
