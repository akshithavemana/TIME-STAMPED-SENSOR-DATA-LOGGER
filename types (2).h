//types.h
/*------------------------------------------------------------
File: types.h
Purpose:
Defines user-friendly data type aliases for portability
and readability in embedded C programming.

These typedefs ensure consistent data sizes across
the LPC214x ARM7 microcontroller application.
------------------------------------------------------------*/

//------------------------------------------------------------
// 8-bit data types
//------------------------------------------------------------

// Unsigned 8-bit integer (0 to 255)
typedef unsigned char u8;

// Signed 8-bit integer (-128 to +127)
typedef signed char s8;

//------------------------------------------------------------
// 16-bit data types
//------------------------------------------------------------

// Unsigned 16-bit integer (0 to 65535)
typedef unsigned short int u16;

// Signed 16-bit integer (-32768 to +32767)
typedef signed short int s16;

//------------------------------------------------------------
// 32-bit data types
//------------------------------------------------------------

// Unsigned 32-bit integer (0 to 4,294,967,295)
typedef unsigned long int u32;

// Signed 32-bit integer (-2,147,483,648 to +2,147,483,647)
typedef signed long int s32;

//------------------------------------------------------------
// Floating-point data types
//------------------------------------------------------------

// 32-bit floating point number (single precision)
typedef float f32;

// 64-bit floating point number (double precision)
typedef double f64;
