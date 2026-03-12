//defines.h
/*------------------------------------------------------------
File: defines.h
Purpose:
Provides commonly used bit manipulation macros for
embedded systems programming on LPC21xx microcontrollers.

These macros simplify:
- Setting, clearing, toggling bits
- Writing single bits, nibbles, bytes, and half-words
- Reading individual bit values from registers
------------------------------------------------------------*/

//------------------------------------------------------------
// Bit Manipulation Macros
//------------------------------------------------------------

//------------------------------------------------------------
// Macro: SETBIT
// Purpose: Set (make logic 1) a specific bit in a register
// WORD -> Register or variable
// BP   -> Bit position (0–31)
//------------------------------------------------------------
#define SETBIT(WORD,BP) WORD |= (1<<BP)

//------------------------------------------------------------
// Macro: CLRBIT
// Purpose: Clear (make logic 0) a specific bit in a register
//------------------------------------------------------------
#define CLRBIT(WORD,BP) WORD &= ~(1<<BP)

//------------------------------------------------------------
// Macro: CPLBIT
// Purpose: Complement (toggle) a specific bit in a register
//------------------------------------------------------------
#define CPLBIT(WORD,BP) WORD ^= (1<<BP)

//------------------------------------------------------------
// Macro: WRITEBIT
// Purpose: Write a specific value (0 or 1) to a bit position
// BIT -> Value to write (0 or 1)
//------------------------------------------------------------
#define WRITEBIT(WORD,BP,BIT) \
        WORD = ((WORD & ~(1<<BP)) | (BIT<<BP))

//------------------------------------------------------------
// Macro: WRITENIBBLE
// Purpose: Write a 4-bit nibble at a specified bit position
//------------------------------------------------------------
#define WRITENIBBLE(WORD,SBP,NIBBLE) \
        WORD = ((WORD & ~(0xF<<SBP)) | (NIBBLE<<SBP))

//------------------------------------------------------------
// Macro: WRITEBYTE
// Purpose: Write an 8-bit byte at a specified bit position
//------------------------------------------------------------
#define WRITEBYTE(WORD,SBP,BYTE) \
        WORD = ((WORD & ~(0xFF<<SBP)) | (BYTE<<SBP))

//------------------------------------------------------------
// Macro: WRITEHWORD
// Purpose: Write a 16-bit half-word at a specified bit position
//------------------------------------------------------------
#define WRITEHWORD(WORD,SBP,HWORD) \
        WORD = ((WORD & ~(0xFFFF<<SBP)) | (HWORD<<SBP))

//------------------------------------------------------------
// Macro: READBIT
// Purpose: Read the value (0 or 1) of a specific bit
// Return : Bit value at the given position
//------------------------------------------------------------
#define READBIT(WORD,BP) ((WORD>>BP) & 1)
