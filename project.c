/*------------------------------------------------------------
File: project.c
Purpose:
Main application file for LPC214x ARM7 MCU.

This program:
- Initializes RTC, LCD, UART, ADC, Keypad
- Reads temperature using LM35 via ADC
- Displays system information on LCD
- Allows user to enter EDIT mode using a switch
- Controls LED and buzzer based on conditions
------------------------------------------------------------*/

//------------------------------------------------------------
// Header file containing LPC214x register definitions
//------------------------------------------------------------
#include <lpc214x.h>

//------------------------------------------------------------
// Application-specific header files
//------------------------------------------------------------
#include "rtc.h"                 // Real Time Clock driver
#include "lcd.h"                 // LCD interface functions
#include "uart.h"               // UART communication
#include "lm35.h"                // LM35 temperature sensor
#include "adc_defines.h"         // ADC register definitions
#include "adc.h"                // ADC1 driver functions
#include "DisplayInformation.h"  // LCD display routines
#include "defines.h"             // Common macros and definitions
#include "KeyPd.h"               // Keypad driver

//------------------------------------------------------------
// Macro definitions
//------------------------------------------------------------

// Switch connected to P0.18
#define SW 18

// Default temperature set point
#define SET_POINT 45

//------------------------------------------------------------
// Global variables
//------------------------------------------------------------

// Flag to indicate EDIT mode status
u32 edit_flag = 0;

// Variable to store temperature set point
u32 set_point = SET_POINT;

//------------------------------------------------------------
// Function: main
// Purpose : Entry point of the application
//------------------------------------------------------------
int main()
{
        //--------------------------------------------------------
        // Configure P0.16 and P0.17 as output pins
        // P0.16 -> LED
        // P0.17 -> Buzzer
        //--------------------------------------------------------
        IODIR0 |= (1 << 16) | (1 << 17);

        //--------------------------------------------------------
        // Turn ON LED initially
        //--------------------------------------------------------
        IOSET0 = (1 << 16);

        //--------------------------------------------------------
        // Initialize Real Time Clock (RTC)
        //--------------------------------------------------------
        RTC_Init();

        //--------------------------------------------------------
        // Initialize LCD module
        //--------------------------------------------------------
        InitLCD();

        //--------------------------------------------------------
        // Initialize UART for serial communication
        //--------------------------------------------------------
        InitUART();

        //--------------------------------------------------------
        // Initialize ADC channel 1 for LM35 temperature sensor
        //--------------------------------------------------------
        Init_ADC(CH1);

        //--------------------------------------------------------
        // Initialize Keypad
        //--------------------------------------------------------
        KeyPdInit();

        //--------------------------------------------------------
        // Display initial information on LCD
        //--------------------------------------------------------
        SetInformation();

        //--------------------------------------------------------
        // Infinite loop
        //--------------------------------------------------------
  while (1)
        {
                //----------------------------------------------------
                // Check if switch (SW) is pressed
                // Active LOW: pressed when logic level is 0
                //----------------------------------------------------
                if (READBIT(IOPIN0, SW) == 0)
                {
                        // Enter EDIT mode
                        edit_flag = 1;
                }

                //----------------------------------------------------
                // If EDIT mode is enabled
                //----------------------------------------------------
                if (edit_flag == 1)
                {
                        // Clear LCD screen
                        CmdLCD(0x01);

                        // Call EDIT mode routine
                        EditMode();

                        // Clear LCD again after editing
                        CmdLCD(0x01);
                }
                else
                {
                        //------------------------------------------------
                        // Normal display mode
                        //------------------------------------------------
                        DisplayInformation();
                }
        }
}
