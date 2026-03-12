//KeyPad.c
/*------------------------------------------------------------
File: KeyPad.c
Purpose:
Source file for interfacing a 4x4 matrix keypad with
LPC21xx/LPC214x ARM7 microcontroller.

This file provides:
- Keypad initialization
- Column status detection
- Key value identification using row-column scanning
------------------------------------------------------------*/

#include <LPC21xx.h>        // LPC21xx/LPC214x register definitions
#include "KeyPdDefines.h"  // Keypad row, column, and lookup table definitions

/*------------------------------------------------------------
Function: KeyPdInit
Purpose :
Initializes keypad interface pins.

This function:
- Configures row pins as output
- Sets initial row output values to logic LOW
------------------------------------------------------------*/
void KeyPdInit(void)
{
        //----------------------------------------------------------
        // Configure P1.16 – P1.19 as output pins (rows)
        //----------------------------------------------------------
        IODIR1 |= ((1 << R0) | (1 << R1) | (1 << R2) | (1 << R3));

        //----------------------------------------------------------
        // Initialize all row pins to LOW
        //----------------------------------------------------------
        IOCLR1 = ((1 << R0) | (1 << R1) | (1 << R2) | (1 << R3));
}

/*------------------------------------------------------------
Function: ColStat
Purpose :
Checks whether any key is pressed on the keypad.

Return:
1 -> No key pressed (all columns HIGH)
0 -> Key pressed (any column LOW)
------------------------------------------------------------*/
u8 ColStat(void)
{
        //----------------------------------------------------------
        // Read column pins P1.20 – P1.23
        //----------------------------------------------------------
        if ((((IOPIN1 >> 20) & 0x0F) == 0x0F))
                return 1;     // No key pressed
        else
                return 0;     // Key pressed
}

/*------------------------------------------------------------
Function: KeyVal
Purpose :
Determines which key is pressed on the keypad.

Method:
- Sequentially drives each row LOW
- Reads column inputs to detect pressed key
- Uses lookup table (LUT) to return key value

Return:
Key value from LUT corresponding to pressed key
------------------------------------------------------------*/
u8 KeyVal(void)
{
        char row_val = 0, col_val = 0;

        //----------------------------------------------------------
        // Activate Row 0 and deactivate other rows
        //----------------------------------------------------------
        IOCLR1 = (1 << R0);
        IOSET1 = ((1 << R1) | (1 << R2) | (1 << R3));

        if ((((IOPIN1 >> 20) & 0x0F) != 0x0F))
        {
                row_val = 0;
                goto colcheck;
        }

        //----------------------------------------------------------
        // Activate Row 1
        //----------------------------------------------------------
        IOCLR1 = (1 << R1);
        IOSET1 = ((1 << R0) | (1 << R2) | (1 << R3));

        if ((((IOPIN1 >> 20) & 0x0F) != 0x0F))
        {
                row_val = 1;
                goto colcheck;
        }

        //----------------------------------------------------------
        // Activate Row 2
        //----------------------------------------------------------
        IOCLR1 = (1 << R2);
        IOSET1 = ((1 << R0) | (1 << R1) | (1 << R3));

        if ((((IOPIN1 >> 20) & 0x0F) != 0x0F))
        {
                row_val = 2;
                goto colcheck;
        }

        //----------------------------------------------------------
        // Activate Row 3
        //----------------------------------------------------------
        IOCLR1 = (1 << R3);
        IOSET1 = ((1 << R0) | (1 << R1) | (1 << R2));

        if ((((IOPIN1 >> 20) & 0x0F) != 0x0F))
                row_val = 3;

        //----------------------------------------------------------
        // Column detection
        //----------------------------------------------------------
        colcheck:
        if (((IOPIN1 >> C0) & 1) == 0)
                col_val = 0;
        else if (((IOPIN1 >> C1) & 1) == 0)
                col_val = 1;
        else if (((IOPIN1 >> C2) & 1) == 0)
                col_val = 2;
        else
                col_val = 3;

        //----------------------------------------------------------
        // Reset all row pins to LOW after key detection
        //----------------------------------------------------------
        IOCLR1 = ((1 << R0) | (1 << R1) | (1 << R2) | (1 << R3));

        //----------------------------------------------------------
        // Return key value from lookup table
        //----------------------------------------------------------
        return (LUT[row_val][col_val]);
}

