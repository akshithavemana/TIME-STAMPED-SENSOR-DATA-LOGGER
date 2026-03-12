//DisplayInformation.c
/*------------------------------------------------------------
File: DisplayInformation.c
Purpose:
Handles display and editing of RTC, temperature, and set-point
information on LCD and UART for LPC21xx microcontroller.

This file provides:
- Initializing RTC and default values
- Displaying time, date, day, and temperature
- Editing RTC and temperature set-point via keypad
- Helper functions for numeric input and date validation
------------------------------------------------------------*/

#include <lpc214x.h>
#include "types.h"
#include "rtc.h"
#include "lcd.h"
#include "uart.h"
#include "lm35.h"
#include "macros.h"
#include "KeyPd.h"
#include "delay.h"
#include "DisplayInformation.h"


//------------------------------------------------------------
// External flags and set-point
//------------------------------------------------------------
extern u32 edit_flag, set_point;

//------------------------------------------------------------
// Local variables for menu choices and value input
//------------------------------------------------------------
u32 choice, choice1, value;

//------------------------------------------------------------
// Function: SetInformation
// Purpose : Initialize RTC with default time, date, and day
//------------------------------------------------------------
void SetInformation()
{
        SetRTCTimeInfo(HR, MINUTE, SECOND);
        SetRTCDateInfo(DATE, MON, YR);
        SetRTCDay(DAY);
}

//------------------------------------------------------------
// Function: DisplayInformation
// Purpose : Display current RTC info, day, and temperature
//           on LCD and send alerts/info via UART
//------------------------------------------------------------
void DisplayInformation()
{
        GetRTCTimeInfo(&hour, &min, &sec);
        DisplayRTCTime(hour, min, sec);

        GetRTCDateInfo(&date, &month, &year);
        DisplayRTCDate(date, month, year);

        GetRTCDay(&day);
        DisplayRTCDay(day);

        // Read temperature from LM35 sensor in Celsius
        temp = Read_LM35('C');
        TempDisplay(temp);

        // Check against set-point and control outputs
        if(temp < set_point)
        {
                IOSET0 = (1 << 16);  // LED ON
                IOSET0 = (1 << 17);  // Buzzer ON (or indicator)

                // Periodic UART update every minute
                if(min == check && sec == SECOND)
                //if(min == check)
                {
                        UARTTxStr("[INFO] ");
                        UARTTxStr("Temp:");
                        UARTTxU32(temp);
                        UARTTxStr("C @");
                        DisplayUARTTime(hour, min, sec);
                        DisplayUARTDate(date, month, year);
                        UARTTxStr("\r\n");

                        check++;
                        if(check > 59)
                                check = 0;
                }
        }
        else
        {
                IOCLR0 = (1 << 16);  // LED OFF
                IOCLR0 = 1 << 17;    // Buzzer OFF

                UARTTxStr("[ALERT] ");
                UARTTxStr("Temp:");
                UARTTxU32(temp);
                UARTTxStr("C @");
                DisplayUARTTime(hour, min, sec);
                DisplayUARTDate(date, month, year);
                UARTTxStr("-OVER TEMP!\r\n");
        }
}

//------------------------------------------------------------
// Function: EditMode
// Purpose : Display menu for editing RTC and set-point
//           Allows user to select option via keypad
//------------------------------------------------------------
void EditMode()
{
        // Display menu on LCD
        StrLCD("1.EDIT RTC INFO");
        CmdLCD(0xC0);
        StrLCD("2.SET POINT");
        CmdLCD(0xCB);
        StrLCD("3.EXIT");

        UARTTxStr("***Time editing Mode Activated***\r\n");

        while(1)
        {
                while(ColStat());       // wait for key press
                delay_ms(10);           // debounce
                choice = KeyVal();      // get user choice
                while(!ColStat());      // wait for key release

                switch(choice)
                {
                        case 1:
                                RTCedit();
                                // Redisplay menu
                                CmdLCD(0x01); CmdLCD(0x80);
                                StrLCD("1.EDIT RTC INFO");
                                CmdLCD(0xC0);
                                StrLCD("2.SET POINT");
                                CmdLCD(0xCB);
                                StrLCD("3.EXIT");
                                break;

                        case 2:
                                EditSetPoint();
                                // Redisplay menu
                                CmdLCD(0x01); CmdLCD(0x80);
                                StrLCD("1.EDIT RTC INFO");
                                CmdLCD(0xC0);
                                StrLCD("2.SET POINT");
                                CmdLCD(0xCB);
                                StrLCD("3.EXIT");
                                break;

                        case 3:
                                edit_flag = 0;       // Exit edit mode
                                return;

                        default:
                                break;
                }
        }
}

//------------------------------------------------------------
// Function: RTCedit
// Purpose : Edit RTC time/date/day via keypad input
//------------------------------------------------------------
void RTCedit(void)
{
        unsigned char choice1;
        unsigned int value;

        // Display RTC edit menu
        CmdLCD(0x80);
        StrLCD("1.H 2.M 3.S 4.D");
        CmdLCD(0xC0);
        StrLCD("5.M 6.Y 7.DY8.E");

        while(1)
        {
                while(ColStat());      // wait for key press
                choice1 = KeyVal();    // read key
                delay_ms(10);          // debounce
                while(!ColStat());     // wait for release
                CmdLCD(0x01);          // clear LCD

                switch(choice1)
                {
                        case 1: // Hour
                                StrLCD("Enter hour: ");
                                value = ReadNumber();
                                if(value < 24)
                                        HOUR = value;
                                else
                                {
                                        CmdLCD(0x01);
                                        StrLCD("INVALID INPUT");
                                }
                                break;

                        case 2: // Minute
                                StrLCD("Enter minute:");
                                value = ReadNumber();
                                if(value < 60)
                                        MIN = value;
                                else
                                {
                                        CmdLCD(0x01);
                                        StrLCD("INVALID INPUT");
                                }
                                break;

                        case 3: // Second
                                StrLCD("Enter second:");
                                value = ReadNumber();
                                if(value < 60)
                                        SEC = value;
                                else
                                {
                                        CmdLCD(0x01);
                                        StrLCD("INVALID INPUT");
                                }
                                break;

                        case 4: // Date
                                StrLCD("Enter date:");
                                value = ReadNumber();
                                if(value >= 1 && value <= GetMaxDays(MONTH, YEAR))
                                        DOM = value;
                                else
                                {
                                        CmdLCD(0x01);
                                        StrLCD("NOT UPDATED");
                                        delay_ms(300);
                                }
                                break;

                        case 5: // Month
                                StrLCD("Enter month:");
                                value = ReadNumber();
                                if(value >= 1 && value <= 12)
                                {
                                        if(DOM <= GetMaxDays(value, YEAR))
                                                MONTH = value;
                                        else
                                                goto DOWN;
                                }
                                else
                                DOWN: {
                                                                CmdLCD(0x01);
                                                                StrLCD("INVALID INPUT");
                                                                delay_ms(300);
                                                        }
                                break;

                        case 6: // Year
                                StrLCD("Enter year: ");
                                value = ReadNumber();
                //      if(value >=1000 && value <= 2099)   // Accept only 4-digit year

                                if(DOM <= GetMaxDays(MONTH, value))
                                        YEAR = value;
                else
                                {
                                        CmdLCD(0x01);
                                        StrLCD("NOT UPDATED");
                                        delay_ms(300);
                                }
                                break;

                        case 7: // Day of week
                                StrLCD("Enter day:");
                                value = ReadNumber();
                                if(value <= 6)
                                        DOW = value;
                                else
                                {
                                        CmdLCD(0x01);
                                        StrLCD("NOT UPDATED");
                                        delay_ms(300);
                                }

                                break;

                        case 8: // Exit
                                return;

                        default:
                                break;
                }

                // Redisplay menu after each edit
                delay_ms(1000);
                CmdLCD(0x80); StrLCD("1.H 2.M 3.S 4.D");
                CmdLCD(0xC0); StrLCD("5.M 6.Y 7.DY8.E");
        }
}

//------------------------------------------------------------
// Function: ReadNumber
// Purpose : Read multi-digit numeric input from keypad
// Return  : Entered number as u32
//------------------------------------------------------------
u32 ReadNumber(void)
{
        u8 key;
        u32 num = 0, count;

        while(1)
        {
                while(ColStat());     // wait for key press
                delay_ms(10);
                key = KeyVal();       // read key
                while(!ColStat());    // wait for release

                if(key == 14) break;  // CONFIRM key pressed

                if(key <= 9)           // numeric key
                {
                        count++;
                        num = num * 10 + key;
                        CharLCD(key + '0'); // display digit
                }

                if(key == 15 && count > 0) // BACKSPACE key
                {
                        num /= 10;
                        count--;
                        CmdLCD(0x10); CharLCD(' '); CmdLCD(0x10);
                }
        }

        delay_ms(300);
        return num;
}

//------------------------------------------------------------
// Function: EditSetPoint
// Purpose : Update temperature set-point via keypad
//------------------------------------------------------------
void EditSetPoint(void)
{
        CmdLCD(0x01);
        StrLCD("SET TEMP LIM:");
        set_point = ReadNumber();
        CmdLCD(0x01);
        StrLCD("LIMIT UPDATED");
        delay_ms(800);
}

//------------------------------------------------------------
// Function: GetMaxDays
// Purpose : Return maximum days in a month considering leap year
//------------------------------------------------------------
u8 GetMaxDays(u32 m, u32 y)
{
        switch(m)
        {
                case 1: case 3: case 5: case 7:
                case 8: case 10: case 12: return 31;
                case 4: case 6: case 9: case 11: return 30;
                case 2: return IsLeapYear(y) ? 29 : 28;
                default: return 31;
        }
}

//------------------------------------------------------------
// Function: IsLeapYear
// Purpose : Check if given year is a leap year
// Return  : 1 -> Leap year, 0 -> Not a leap year
//------------------------------------------------------------
u8 IsLeapYear(u32 y)
{
        if((y % 400) == 0) return 1;
        if((y % 100) == 0) return 0;
        if((y % 4) == 0)   return 1;
        return 0;
}
