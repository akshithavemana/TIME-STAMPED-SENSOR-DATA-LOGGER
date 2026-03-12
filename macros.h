//macros.h
/*------------------------------------------------------------
File: macros.h
Purpose:
Defines project-level constants, default RTC values,
set points, and global variables for LPC21xx project.
------------------------------------------------------------*/

#include "types.h"   // User-defined data types

//------------------------------------------------------------
// Default Time and Date Values
//------------------------------------------------------------
#define HR       23       // Default hour (0–23)
#define MINUTE    0       // Default minute (0–59)
#define SECOND   58       // Default second (0–59)

#define DATE     29       // Default day of month (1–31)
#define MON       2       // Default month (1–12)
#define YR     2024       // Default year (4-digit)
#define DAY       4       // Default day of week (0=Sunday, ..., 6=Saturday)

//------------------------------------------------------------
// Project Control Macros
//------------------------------------------------------------
#define SET_POINT 45      // Default set point value for temperature control

//------------------------------------------------------------
// Global Variables
//------------------------------------------------------------
u32 hour, min, sec;       // Variables to hold current time
u32 date, month, year;    // Variables to hold current date
u32 day;                  // Variable to hold day of week
u32 check = 0;            // General-purpose flag/check variable
static u32 temp;           // Static variable for storing temperature readings
