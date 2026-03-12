//rtc.h
/*------------------------------------------------------------
File: rtc.h
Purpose:
Header file for Real Time Clock (RTC) module.

This file contains:
- Function prototypes for RTC initialization
- Functions to get, set, and display time, date, and day
- Uses 32-bit unsigned integers for RTC parameters
------------------------------------------------------------*/

#ifndef RTC_H
#define RTC_H

//------------------------------------------------------------
// Include user-defined data type definitions
//------------------------------------------------------------
#include "types.h"

//------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------

//------------------------------------------------------------
// Function: RTC_Init
// Purpose : Initialize the RTC peripheral
//           Configures clock source and enables RTC
//------------------------------------------------------------
void RTC_Init(void);

//------------------------------------------------------------
// Function: GetRTCTimeInfo
// Purpose : Read current time from RTC
//           hour   -> pointer to hour value
//           minute -> pointer to minute value
//           second -> pointer to second value
//------------------------------------------------------------
void GetRTCTimeInfo(u32 *, u32 *, u32 *);

//------------------------------------------------------------
// Function: DisplayRTCTime
// Purpose : Display RTC time (HH:MM:SS) on output device
//------------------------------------------------------------
void DisplayRTCTime(u32, u32, u32);

//------------------------------------------------------------
// Function: GetRTCDateInfo
// Purpose : Read current date from RTC
//           day   -> pointer to day
//           month -> pointer to month
//           year  -> pointer to year
//------------------------------------------------------------
void GetRTCDateInfo(u32 *, u32 *, u32 *);

//------------------------------------------------------------
// Function: DisplayRTCDate
// Purpose : Display RTC date (DD/MM/YYYY) on output device
//------------------------------------------------------------
void DisplayRTCDate(u32, u32, u32);

//------------------------------------------------------------
// Function: SetRTCTimeInfo
// Purpose : Set RTC time values
//           hour, minute, second are written to RTC registers
//------------------------------------------------------------
void SetRTCTimeInfo(u32, u32, u32);

//------------------------------------------------------------
// Function: SetRTCDateInfo
// Purpose : Set RTC date values
//           day, month, year are written to RTC registers
//------------------------------------------------------------
void SetRTCDateInfo(u32, u32, u32);

//------------------------------------------------------------
// Function: GetRTCDay
// Purpose : Read current day of week from RTC
//           (e.g., Monday, Tuesday, etc.)
//------------------------------------------------------------
void GetRTCDay(u32 *);

//------------------------------------------------------------
// Function: DisplayRTCDay
// Purpose : Display current day of week on output device
//------------------------------------------------------------
void DisplayRTCDay(u32);

//------------------------------------------------------------
// Function: SetRTCDay
// Purpose : Set day of week in RTC
//------------------------------------------------------------
void SetRTCDay(u32);

#endif
