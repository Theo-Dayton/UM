/********************************************************************
* instructions.h
* Assignment: UM (HW6)
* Authors: Yuehan (Eunice) Dai (ydai05), Grace Ye (gye01)
* Date: 11/23/21
* Summary: This is the interface of instructions, which
*          takes care of the getting of values in instructions
********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "memory.h"

/*
* Name: loadInstructions
* Purpose: Read in the instructions from the input file into the UM
* Input: A UM, a file pointer to the input of instructions
* Input Specification: The file pointer should point to a valid file
* Output: None, but the instructions are loaded into the UM
*/
void loadInstructions(UMachine um, FILE *input);

/*
* Name: getInstruction
* Purpose: Get the next instruction from the UM
* Input: A UM, a uint32_t program counter
* Input Specification: None
* Output: Returns the next instruction
*/
Um_instruction getInstruction(UMachine um, uint32_t programCounter);

/*
* Name: instructionLength
* Purpose: Get length of instruction
* Input: A file pointer to the input of instructions
* Input Specification: The file pointer should point to a valid file
* Output: Returns length of instruction
*/
unsigned instructionLength(FILE *input);

/*
* Name: getOP
* Purpose: Get OP code of instruction
* Input: A UM instruction
* Input Specification: None
* Output: Returns OP code of instruction
*/
Um_opcode getOP(Um_instruction instruction);

/*
* Name: getRA
* Purpose: Get RA of instruction
* Input: A UM instruction
* Input Specification: The UM instruction must not be a load value instruction
* Output: Returns RA code of instruction
*/
Um_register getRA(Um_instruction instruction);

/*
* Name: getRB
* Purpose: Get RB of instruction
* Input: A UM instruction
* Input Specification: None
* Output: Returns RB code of instruction
*/
Um_register getRB(Um_instruction instruction);

/*
* Name: getRC
* Purpose: Get RC of instruction
* Input: A UM instruction
* Input Specification: None
* Output: Returns RC code of instruction
*/
Um_register getRC(Um_instruction instruction);

/*
* Name: getVal
* Purpose: Get value of instruction
* Input: A UM instruction
* Input Specification: None
* Output: Returns value of instruction
*/
Um_value getVal(Um_instruction instruction);

/*
* Name: getLVRA
* Purpose: Get RA of load value instruction
* Input: A UM instruction
* Input Specification: The UM instruction must be a load value instruction
* Output: Returns RA code of load value instruction
*/
Um_opcode getLVRA(Um_instruction instruction);

/*
* Name: readWord
* Purpose: Reads in the information and packs it into a word
* Input: A file pointer to the input of instructions
* Input Specification: The file pointer should point to a valid file
* Output: Returns the bitpacked word
*/
Um_instruction readWord(FILE *input);