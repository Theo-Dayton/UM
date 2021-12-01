/********************************************************************
* memory.h
* Assignment: UM (HW6)
* Authors: Yuehan (Eunice) Dai (ydai05), Grace Ye (gye01)
* Date: 11/23/21
* Summary: This is the interface of memory, which
*          deals with all memory allocation and deallocation
********************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <mem.h>
#include <except.h>

#include "bitpack.h"
#include "uarray.h"
#include "seq.h"
#include "stack.h"

#ifndef MEMORY
#define MEMORY

typedef struct UMachine {
    UArray_T registers;  /* registers */
    Seq_T memory; /* main memory */
    Seq_T freeMemory; /* free memory used for later use*/
    uint32_t programCounter;
} *UMachine;

typedef uint32_t Um_instruction;
typedef uint32_t Um_value;

typedef enum Um_opcode {
        CMOV = 0, SLOAD, SSTORE, ADD, MUL, DIV,
        NAND, HALT, ACTIVATE, INACTIVATE, OUT, IN, LOADP, LV
} Um_opcode;

typedef enum Um_register { r0 = 0, r1, r2, r3, r4, r5, r6, r7 } Um_register;

/*
* Name: newUM
* Purpose: Creates a new UM and initializes it
* Input: None
* Input Specification: None
* Output: Returns the new UM
*/
extern UMachine newUM();

/*
* Name: initializeRegisters
* Purpose: Initializes all registers to 0
* Input: A UM
* Input Specification: None
* Output: None, but all registers initialized
*/
void initializeRegisters(UMachine um);

/*
* Name: getRegVal
* Purpose: Gets a register value
* Input: A UM, an index from which to get the register value
* Input Specification: Index should be a value between 0 and 7 inclusive
* Output: Value at that given index of the register returned
*/
Um_value getRegVal(UMachine um, Um_register index);

/*
* Name: setRegVal
* Purpose: Sets a register value
* Input: A UM, an index at which to set the register value, the value to set
* Input Specification: Index should be a value between 0 and 7 inclusive
* Output: Value at that given index of the register set to the provided value
*/
void setRegVal(UMachine um, Um_register index, Um_value val);

/*
* Name: getSegVal
* Purpose: Gets a value within a given segment
* Input: A UM, the segment block, the index within the segment block
* Input Specification: The segment block and the index should be values that
*                      are actually within the memory at this point in time
* Output: Returns value at that given segment at that given index within the
*         segment block
*/
Um_value getSegVal(UMachine um, uint32_t block, uint32_t index);

/*
* Name: getSeg
* Purpose: Gets value of a segment
* Input: A UM, the segment block
* Input Specification: The segment block should be a value that is
*                      actually within the memory at this point in time
* Output: Returns value at that given segment
*/
UArray_T getSeg(UMachine um, uint32_t block);

/*
* Name: setSegVal
* Purpose: Sets a value within a given segment
* Input: A UM, the segment block, the index within the segment block, 
*        the value to set
* Input Specification: The segment block and the index should be values that
*                      are actually within the memory at this point in time
* Output: None, but sets value at that given segment at that given index 
*         within the segment block
*/
void setSegVal(UMachine um, uint32_t blockIndex, uint32_t index, Um_value val);

/*
* Name: setSeg
* Purpose: Sets value of a segment into a specific block
* Input: A UM, the block index, the segment
* Input Specification: The block index should be a value that is
*                      actually within the memory at this point in time
* Output: None, but sets value of segment into that specific block
*/
void setSeg(UMachine um, uint32_t blockIndex, UArray_T segment);

/*
* Name: freeSeg
* Purpose: Frees a segment of main memory in the UM
* Input: A UM, the index
* Input Specification: The index should be a value that is
*                      actually within the memory at this point in time
* Output: None, but frees segment at the specified index
*/
void freeSeg(UMachine um, uint32_t index);

/*
* Name: freeMainMemory
* Purpose: Frees the main memory of the UM
* Input: A UM
* Input Specification: None
* Output: None, but main memory freed
*/
void freeMainMemory(UMachine um);

#endif