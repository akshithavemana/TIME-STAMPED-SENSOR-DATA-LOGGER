//DisplayInformation.h
/*------------------------------------------------------------
File: DisplayInformation.h
Purpose:
Header file for managing display and editing of RTC,
temperature, and set-point information for LPC21xx.

This file provides:
- Function prototypes for displaying and editing RTC and temperature
- Utility functions for numeric input and date validation
------------------------------------------------------------*/

#include "types.h"   // User-defined data types

//------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------

//------------------------------------------------------------
// Function: DisplayInformation
// Purpose : Display current RTC time, date, day, and temperature
//           on LCD and send updates via UART if required
//------------------------------------------------------------
void DisplayInformation(void);

//------------------------------------------------------------
// Function: SetInformation
// Purpose : Initialize RTC with default time, date, and day
//------------------------------------------------------------
void SetInformation(void);

//------------------------------------------------------------
// Function: EditMode
// Purpose : Provide menu interface for editing RTC info and
//           temperature set-point using keypad
//------------------------------------------------------------
void EditMode(void);

//------------------------------------------------------------
// Function: ReadNumber
// Purpose : Read multi-digit numeric input from keypad
// Return  : Entered number as u32
//------------------------------------------------------------
u32 ReadNumber(void);

//------------------------------------------------------------
// Function: RTCedit
// Purpose : Edit individual RTC fields (hour, minute, second,
//           date, month, year, day) via keypad input
//------------------------------------------------------------
void RTCedit(void);

//------------------------------------------------------------
// Function: EditSetPoint
// Purpose : Update temperature set-point via keypad input
//------------------------------------------------------------
void EditSetPoint(void);

//------------------------------------------------------------
// Function: GetMaxDays
// Purpose : Return maximum days in a given month considering
//           leap year
// Parameters:
//   m -> Month (1–12)
//   y -> Year (4-digit)
// Return : Maximum number of days in the month
//------------------------------------------------------------
u8 GetMaxDays(u32 m, u32 y);

//------------------------------------------------------------
// Function: IsLeapYear
// Purpose : Check if a given year is a leap year
// Parameter:
//   y -> Year (4-digit)
// Return : 1 -> Leap year, 0 -> Not a leap year
//------------------------------------------------------------
u8 IsLeapYear(u32 y);
