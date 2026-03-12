//lcd.h
/*------------------------------------------------------------
File: lcd.h
Purpose:
Header file for LCD interface module.

This file contains:
- Function prototypes for initializing and controlling LCD
- Display functions for characters, strings, integers, floats
- Custom character storage support
------------------------------------------------------------*/

#include "types.h"   // User-defined data type definitions

//------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------

//------------------------------------------------------------
// Function: InitLCD
// Purpose : Initialize LCD module
//           Configures LCD in required mode (8-bit/4-bit)
//------------------------------------------------------------
void InitLCD(void);

//------------------------------------------------------------
// Function: CmdLCD
// Purpose : Send command byte to LCD
//           Used for cursor control, clearing display, etc.
//------------------------------------------------------------
void CmdLCD(u8);

//------------------------------------------------------------
// Function: CharLCD
// Purpose : Display a single character on LCD
//------------------------------------------------------------
void CharLCD(u8);

//------------------------------------------------------------
// Function: DispLCD
// Purpose : Display raw data/byte on LCD
//------------------------------------------------------------
void DispLCD(u8);

//------------------------------------------------------------
// Function: StrLCD
// Purpose : Display a null-terminated string on LCD
//------------------------------------------------------------
void StrLCD(u8 *);

//------------------------------------------------------------
// Function: IntLCD
// Purpose : Display signed integer value on LCD
//------------------------------------------------------------
void IntLCD(s32);

//------------------------------------------------------------
// Function: FltLCD
// Purpose : Display floating-point number on LCD
//------------------------------------------------------------
void FltLCD(f32);

//------------------------------------------------------------
// Function: StoreCustCharFont
// Purpose : Store custom character font patterns in CGRAM
//------------------------------------------------------------
void StoreCustCharFont(void);

//------------------------------------------------------------
// Function: TempDisplay
// Purpose : Display temperature value on LCD
//           Used for sensor (LM35) temperature output
//------------------------------------------------------------
void TempDisplay(u32);
