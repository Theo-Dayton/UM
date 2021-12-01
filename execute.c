/********************************************************************
* execute.c
* Assignment: UM (HW6)
* Authors: Yuehan (Eunice) Dai (ydai05), Grace Ye (gye01)
* Date: 11/23/21
* Summary: This is the implementation of execute, which
*          contains all of the possible um instructions'
*          implementations
********************************************************************/

#include <except.h>
#include "execute.h"
/*
* Name: execute
* Purpose: Executes an instruction
* Input: A UM, OP code, RA, RB, RC, Load Value RA, Value
* Output: None, but instruction executed
*/
void execute(UMachine um, Um_opcode op_code, 
                   Um_register ra, 
                   Um_register rb, 
                   Um_register rc,
                   Um_register LVra,
                   Um_value val)
{
    switch(op_code) {
        case CMOV:
            condMove(um, ra, rb, rc);
            break;

        case SLOAD:
            segLoad(um, ra, rb, rc);
            break;

        case SSTORE:
            segStore(um, ra, rb, rc);
            break;

        case ADD:
            addition(um, ra, rb, rc);
            break;

        case MUL:
            multiplication(um, ra, rb, rc);
            break;

        case DIV:
            division(um, ra, rb, rc);
            break;
            
        case NAND:
            nand(um, ra, rb, rc);
            break;

        case HALT:
            halt(um);
            break;

        case ACTIVATE:
            map(um, rb, rc);
            break;

        case INACTIVATE:
            unmap(um, rc);
            break;

        case OUT:
            output(um, rc);
            break;

        case IN:
            input(um, rc);
            break;

        case LOADP:
            loadProg(um, rb, rc);
            break;

        case LV:
            loadVal(um, LVra, val);
            break;

    }
}

/*
* Name: condMove
* Purpose: Runs the conditional move instruction; if value in RC does not
*          equal 0, set value of RB into RA
* Input: A UM, RA, RB, RC
* Output: None, but instruction executed
*/
void condMove(UMachine um, Um_register A, Um_register B, Um_register C)
{

    if (getRegVal(um, C) != 0) {
        setRegVal(um, A, getRegVal(um, B));
    }
}

/*
* Name: segLoad
* Purpose: Runs the segmented load instruction; store the RB segment's 
*          RC word into RA
* Input: A UM, RA, RB, RC
* Output: None, but instruction executed
*/
void segLoad(UMachine um, Um_register A, Um_register B, Um_register C)
{
    Um_value val = getSegVal(um, B, C);
    setRegVal(um, A, val);
}

/*
* Name: segStore
* Purpose: Runs the segmented store instruction; store the RC value into 
*          the RA segment's RB word
* Input: A UM, RA, RB, RC
* Output: None, but instruction executed
*/
void segStore(UMachine um, Um_register A, Um_register B, Um_register C)
{
    Um_value val = getRegVal(um, C);
    setSegVal(um, A, B, val);
}

/*
* Name: addition
* Purpose: Runs the add instruction; add RB and RC values and store in RA
* Input: A UM, RA, RB, RC
* Output: None, but instruction executed
*/
void addition(UMachine um, Um_register A, Um_register B, Um_register C)
{
    int valB = getRegVal(um, B);
    int valC = getRegVal(um, C);
    Um_value val = valB + valC;
    setRegVal(um, A, val);
}

/*
* Name: multiplication
* Purpose: Runs the multiplication instruction; multiply RB and RC values 
*          and store in RA
* Input: A UM, RA, RB, RC
* Output: None, but instruction executed
*/
void multiplication(UMachine um, Um_register A, Um_register B, Um_register C)
{
    int valB = getRegVal(um, B);
    int valC = getRegVal(um, C);
    Um_value val = valB * valC;
    setRegVal(um, A, val);
}

/*
* Name: division
* Purpose: Runs the division instruction; divide RB and RC values 
*          and store in RA
* Input: A UM, RA, RB, RC
* Output: None, but instruction executed
*/
void division(UMachine um, Um_register A, Um_register B, Um_register C)
{
    Um_value valB = getRegVal(um, B);
    Um_value valC = getRegVal(um, C);
    assert(valC != 0);
    Um_value val = valB / valC;
    setRegVal(um, A, val);
}

/*
* Name: nand
* Purpose: Runs the nand instruction; nand RB and RC values and store in RA
* Input: A UM, RA, RB, RC
* Output: None, but instruction executed
*/
void nand(UMachine um, Um_register A, Um_register B, Um_register C)
{
    Um_value valB = getRegVal(um, B);
    Um_value valC = getRegVal(um, C);
    Um_value val = ~(valB & valC);
    setRegVal(um, A, val);
}

/*
* Name: halt
* Purpose: Runs the halt instruction; stops the program
* Input: A UM
* Output: None, but program stopped
*/
void halt(UMachine um)
{
    um->programCounter = UArray_length(Seq_get(um->memory, 0));
}

/*
* Name: map
* Purpose: Runs the map instruction; maps memory to a block with index RB
*          and length of value of RC
* Input: A UM, RB, RC
* Output: None, but instruction executed
*/
void map(UMachine um, Um_register B, Um_register C)
{
    Um_value val_C = getRegVal(um, C);
    Seq_T memory = um->memory;
    Seq_T freeMemory = um->freeMemory;
    uint32_t length = Seq_length(freeMemory);

    UArray_T tempMem = NULL;
    if (length == 0) { /* if there is no previous reserved space */
        TRY
            tempMem = UArray_new(val_C, sizeof(uint32_t));
        EXCEPT(Mem_Failed)
            fprintf(stderr, "Resources Exhausted\n");
            exit(EXIT_FAILURE);
        END_TRY;
        Seq_addhi(memory, tempMem);
        setRegVal(um, B, Seq_length(memory) - 1);
    } else { 
        TRY
            tempMem = UArray_new(val_C, sizeof(uint32_t));
        EXCEPT(Mem_Failed)
            fprintf(stderr, "Resources Exhausted\n");
            exit(EXIT_FAILURE);
        END_TRY;
        uint32_t index = (uint32_t)(uintptr_t)Seq_remlo(freeMemory);
        Seq_put(memory, index, tempMem);
        setRegVal(um, B, index);
    }
}

/*
* Name: ummap
* Purpose: Runs the ummap instruction; ummaps memory from block with index RC
* Input: A UM, RC
* Output: None, but instruction executed
*/
void unmap(UMachine um, Um_register C)
{
    Um_value index = getRegVal(um, C);
    Seq_T memory = um->memory;
    Seq_T freeMemory = um->freeMemory;

    assert((int)index < Seq_length(memory));
    freeSeg(um, index);
    Seq_put(memory, index, NULL);
    Seq_addlo(freeMemory, (void *)(uintptr_t)index);
}

/*
* Name: output
* Purpose: Runs the output instruction; outputs value in RC to stdout
* Input: A UM, RC
* Output: None, but instruction executed
*/
void output(UMachine um, Um_register C)
{
    Um_value val = getRegVal(um, C);
    
    assert(val <= 255);
    char valc = (char)val;
    putchar(valc);
}

/*
* Name: input
* Purpose: Runs the input instruction; inputs value from stdin to value of RC
* Input: A UM, RC
* Output: None, but instruction executed
*/
void input(UMachine um, Um_register C)
{
    int input = getchar();
    Um_value val;

	if (input == EOF){
        val = ~0;
    } else {
        val = (uint32_t)input;
        assert(val <= 255);
    }	
    setRegVal(um, C, val);
}

/*
* Name: loadProg
* Purpose: Runs the load program instruction; loads the program into the UM at
*          segment of RB index and word of RC index
* Input: A UM, RB, RC
* Output: None, but instruction executed
*/
void loadProg(UMachine um, Um_register B, Um_register C)
{
    Um_value index = getRegVal(um, B);

    if (index != 0){
        UArray_T newInstructions = getSeg(um, B);
        uint32_t length = UArray_length(newInstructions);
        UArray_T copy = UArray_copy(newInstructions, length);

        setSeg(um, 0, copy);   
    }
    
    uint32_t programCounter = getRegVal(um, C);
    Seq_T memory = um->memory;
    uint32_t programLength = UArray_length(Seq_get(memory, 0));
    assert(programCounter < (uint32_t)programLength);
    um->programCounter = programCounter;
}

/*
* Name: loadVal
* Purpose: Runs the load value instruction; loads value into RA
* Input: A UM, RA, value
* Output: None, but instruction executed
*/
void loadVal(UMachine um, Um_register A, Um_value val)
{
    setRegVal(um, A, val);
}
