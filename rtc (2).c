//rtc.c
/*------------------------------------------------------------
File: rtc.c
Purpose:
Source file for Real Time Clock (RTC) operations on LPC21xx/
LPC214x ARM7 microcontroller.

This file provides:
- RTC initialization
- Setting and getting time, date, and day
- Displaying RTC information on LCD
------------------------------------------------------------*/

#include <LPC21xx.H>      // LPC21xx/LPC214x register definitions
#include "rtc_defines.h"  // RTC register macros and constants
#include "types.h"        // User-defined data types
#include "lcd.h"          // LCD interface functions

//------------------------------------------------------------
// Array holding abbreviated names of days of the week
// Index: 0 = Sunday, 1 = Monday, ..., 6 = Saturday
//------------------------------------------------------------
u8 week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};

/*------------------------------------------------------------
Function: RTC_Init
Purpose :
Initializes the Real-Time Clock (RTC).

This function:
- Resets and disables RTC
- Sets prescaler values (if required)
- Enables RTC with appropriate clock source
------------------------------------------------------------*/
void RTC_Init(void)
{
  //----------------------------------------------------------
  // Disable and reset the RTC
  //----------------------------------------------------------
        CCR = RTC_RESET;

#ifdef _LPC2148
  //----------------------------------------------------------
  // Enable RTC and select external clock source (LPC2148)
  //----------------------------------------------------------
        CCR = RTC_ENABLE | RTC_CLKSRC;
#else
  //----------------------------------------------------------
  // Configure prescaler values for RTC clock generation
  //----------------------------------------------------------
        PREINT  = PREINT_VAL;
        PREFRAC = PREFRAC_VAL;

  //----------------------------------------------------------
  // Enable the RTC
  //----------------------------------------------------------
        CCR = RTC_ENABLE;
#endif
}

/*------------------------------------------------------------
Function: SetRTCTimeInfo
Purpose :
Sets the RTC time values.

Parameters:
hour   : Hour value (0 – 23)
minute : Minute value (0 – 59)
second : Second value (0 – 59)
------------------------------------------------------------*/
void SetRTCTimeInfo(u32 hour, u32 minute, u32 second)
{
        HOUR = hour;
        MIN  = minute;
        SEC  = second;
}

/*------------------------------------------------------------
Function: SetRTCDateInfo
Purpose :
Sets the RTC date values.

Parameters:
date  : Day of month (1 – 31)
month : Month (1 – 12)
year  : Year (four digits)
------------------------------------------------------------*/
void SetRTCDateInfo(u32 date, u32 month, u32 year)
{
        DOM   = date;
        MONTH= month;
        YEAR = year;
}

/*------------------------------------------------------------
Function: SetRTCDay
Purpose :
Sets the current day of the week in RTC.

Parameter:
day : Day of week (0 = Sunday, ..., 6 = Saturday)
------------------------------------------------------------*/
void SetRTCDay(u32 day)
{
        DOW = day;
}

/*------------------------------------------------------------
Function: GetRTCTimeInfo
Purpose :
Reads the current time from RTC registers.

Parameters:
hour   : Pointer to store hour
minute : Pointer to store minute
second : Pointer to store second
------------------------------------------------------------*/
void GetRTCTimeInfo(u32 *hour, u32 *minute, u32 *second)
{
        *hour   = HOUR;
        *minute = MIN;
        *second = SEC;
}

/*------------------------------------------------------------
Function: DisplayRTCTime
Purpose :
Displays the current time on LCD in HH:MM:SS format.

Parameters:
hour   : Hour value
minute : Minute value
second : Second value
------------------------------------------------------------*/
void DisplayRTCTime(u32 hour, u32 minute, u32 second)
{
                CmdLCD(0x80);                 // Set cursor to first line
                CharLCD((hour/10) + 48);
                CharLCD((hour%10) + 48);
                CharLCD(':');
                CharLCD((minute/10) + 48);
                CharLCD((minute%10) + 48);
                CharLCD(':');
                CharLCD((second/10) + 48);
                CharLCD((second%10) + 48);
}

/*------------------------------------------------------------
Function: GetRTCDateInfo
Purpose :
Reads the current date from RTC registers.

Parameters:
date  : Pointer to store day of month
month : Pointer to store month
year  : Pointer to store year
------------------------------------------------------------*/
void GetRTCDateInfo(u32 *date, u32 *month, u32 *year)
{
        *date  = DOM;
        *month = MONTH;
        *year  = YEAR;
}

/*------------------------------------------------------------
Function: DisplayRTCDate
Purpose :
Displays the current date on LCD in DD/MM/YYYY format.

Parameters:
date  : Day of month
month : Month
year  : Year
------------------------------------------------------------*/
void DisplayRTCDate(u32 date, u32 month, u32 year)
{
                CmdLCD(0xC0);                 // Set cursor to second line
                CharLCD((date/10) + 48);
                CharLCD((date%10) + 48);
                CharLCD('/');
                CharLCD((month/10) + 48);
                CharLCD((month%10) + 48);
                CharLCD('/');
                IntLCD(year);
}

/*------------------------------------------------------------
Function: GetRTCDay
Purpose :
Reads the current day of the week from RTC.

Parameter:
day : Pointer to store day of week (0 – 6)
------------------------------------------------------------*/
void GetRTCDay(s32 *day)
{
        *day = DOW;
}

/*------------------------------------------------------------
Function: DisplayRTCDay
Purpose :
Displays the current day of the week on LCD.

Parameter:
dow : Day of week (0 = Sunday, ..., 6 = Saturday)
------------------------------------------------------------*/
void DisplayRTCDay(u32 dow)
{
        CmdLCD(0xCB);            // Set LCD cursor position
        StrLCD(week[dow]);       // Display day string
}
