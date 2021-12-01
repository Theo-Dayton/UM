/********************************************************************
* execute.h
* Assignment: UM (HW6)
* Authors: Yuehan (Eunice) Dai (ydai05), Grace Ye (gye01)
* Date: 11/23/21
* Summary: This is the interface of execute, which
*          contains all of the possible um instructions'
*          interfaces
********************************************************************/

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <seq.h>
#include <bitpack.h>
#include <math.h>

#include "memory.h"

#ifndef EXECUTE
#define EXECUTE

/*
* Name: execute
* Purpose: Executes an instruction
* Input: A UM, OP code, RA, RB, RC, Load Value RA, Value
* Input Specification: The OP code should be one of the 14 instructions
* Output: None, but instruction executed
*/
void execute(UMachine um, Um_opcode op_code, 
                   Um_register ra, 
                   Um_register rb, 
                   Um_register rc,
                   Um_register LVra,
                   Um_value val);

/*
* Name: condMove
* Purpose: Runs the conditional move instruction; if value in RC does not
*          equal 0, set value of RB into RA
* Input: A UM, RA, RB, RC
* Input Specification: None
* Output: None, but instruction executed
*/
void condMove(UMachine um, Um_register A, Um_register B, Um_register C);

/*
* Name: segLoad
* Purpose: Runs the segmented load instruction; store the RB segment's 
*          RC word into RA
* Input: A UM, RA, RB, RC
* Input Specification: None
* Output: None, but instruction executed
*/
void segLoad(UMachine um, Um_register A, Um_register B, Um_register C);

/*
* Name: segStore
* Purpose: Runs the segmented store instruction; store the RC value into 
*          the RA segment's RB word
* Input: A UM, RA, RB, RC
* Input Specification: None
* Output: None, but instruction executed
*/
void segStore(UMachine um, Um_register A, Um_register B, Um_register C);

/*
* Name: addition
* Purpose: Runs the add instruction; add RB and RC values and store in RA
* Input: A UM, RA, RB, RC
* Input Specification: None
* Output: None, but instruction executed
*/
void addition(UMachine um, Um_register A, Um_register B, Um_register C);

/*
* Name: multiplication
* Purpose: Runs the multiplication instruction; multiply RB and RC values 
*          and store in RA
* Input: A UM, RA, RB, RC
* Input Specification: None
* Output: None, but instruction executed
*/
void multiplication(UMachine um, Um_register A, Um_register B, Um_register C);

/*
* Name: division
* Purpose: Runs the division instruction; divide RB and RC values 
*          and store in RA
* Input: A UM, RA, RB, RC
* Input Specification: None
* Output: None, but instruction executed
*/
void division(UMachine um, Um_register A, Um_register B, Um_register C);

/*
* Name: nand
* Purpose: Runs the nand instruction; nand RB and RC values and store in RA
* Input: A UM, RA, RB, RC
* Input Specification: None
* Output: None, but instruction executed
*/
void nand(UMachine um, Um_register A, Um_register B, Um_register C);

/*
* Name: halt
* Purpose: Runs the halt instruction; stops the program
* Input: A UM
* Input Specification: None
* Output: None, but program stopped
*/
void halt(UMachine um);

/*
* Name: map
* Purpose: Runs the map instruction; maps memory to a block with index RB
*          and length of value of RC
* Input: A UM, RB, RC
* Input Specification: None
* Output: None, but instruction executed
*/
void map(UMachine um, Um_register B, Um_register C);

/*
* Name: ummap
* Purpose: Runs the ummap instruction; ummaps memory from block with index RC
* Input: A UM, RC
* Input Specification: None
* Output: None, but instruction executed
*/
void unmap(UMachine um, Um_register C);

/*
* Name: output
* Purpose: Runs the output instruction; outputs value in RC to stdout
* Input: A UM, RC
* Input Specification: None
* Output: None, but instruction executed
*/
void output(UMachine um, Um_register C);

/*
* Name: input
* Purpose: Runs the input instruction; inputs value from stdin to value of RC
* Input: A UM, RC
* Input Specification: None
* Output: None, but instruction executed
*/
void input(UMachine um, Um_register C);

/*
* Name: loadProg
* Purpose: Runs the load program instruction; loads the program into the UM at
*          segment of RB index and word of RC index
* Input: A UM, RB, RC
* Input Specification: None
* Output: None, but instruction executed
*/
void loadProg(UMachine um, Um_register B, Um_register C);

/*
* Name: loadVal
* Purpose: Runs the load value instruction; loads value into RA
* Input: A UM, RA, value
* Input Specification: None
* Output: None, but instruction executed
*/
void loadVal(UMachine um, Um_register A, uint32_t val);

#endif