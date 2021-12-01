/********************************************************************
* instructions.c
* Assignment: UM (HW6)
* Authors: Yuehan (Eunice) Dai (ydai05), Grace Ye (gye01)
* Date: 11/23/21
* Summary: This is the implementation of instructions, which
*          takes care of the getting of values in instructions
********************************************************************/

#include "instructions.h"

/*
* Name: loadInstructions
* Purpose: Read in the instructions from the input file into the UM
* Input: A UM, a file pointer to the input of instructions
* Output: None, but the instructions are loaded into the UM
*/
void loadInstructions(UMachine um, FILE *input)
{
    uint32_t length = instructionLength(input);
    
    UArray_T instructions = NULL;
    instructions = UArray_new(length, sizeof(uint32_t));

    for (uint32_t i = 0; i < length; i ++){
        Um_instruction word = readWord(input);
        *(Um_instruction *)UArray_at(instructions, i) = word;
    }
    Seq_addhi(um->memory, instructions); /* 
                                            initialize the memory[0] as a 
                                            sequence to store the
                                            instructions
                                          */
}

/*
* Name: getInstruction
* Purpose: Get the next instruction from the UM
* Input: A UM, a uint32_t program counter
* Output: Returns the next instruction
*/
Um_instruction getInstruction(UMachine um, uint32_t programCounter)
{
    UArray_T instructions = Seq_get(um->memory, 0);
    Um_instruction nextInstruction = *(Um_instruction *)UArray_at(instructions,
                                                        programCounter);

    return nextInstruction;
}

/*
* Name: instructionLength
* Purpose: Get length of instruction
* Input: A file pointer to the input of instructions
* Output: Returns length of instruction
*/
unsigned instructionLength(FILE *input)
{
    fseek(input, 0, SEEK_END);
    unsigned fileLength = ftell(input);
    fseek(input, 0, SEEK_SET);
    return (fileLength / 4);
}

/*
* Name: getOP
* Purpose: Get OP code of instruction
* Input: A UM instruction
* Output: Returns OP code of instruction
*/
Um_opcode getOP(Um_instruction instruction)
{
    uint32_t width = 4;
    uint32_t lsb = 28;
    uint32_t OP = Bitpack_getu(instruction, width, lsb);
    assert(OP < 14);
    return OP;
}

/*
* Name: getRA
* Purpose: Get RA of instruction
* Input: A UM instruction
* Output: Returns RA code of instruction
*/
Um_register getRA(Um_instruction instruction)
{
    uint32_t width = 3;
    uint32_t lsb = 6;
    uint32_t RA = Bitpack_getu(instruction, width, lsb);
    assert(RA < 8);
    return RA;
}

/*
* Name: getRB
* Purpose: Get RB of instruction
* Input: A UM instruction
* Output: Returns RB code of instruction
*/
Um_register getRB(Um_instruction instruction)
{
    uint32_t width = 3;
    uint32_t lsb = 3;
    uint32_t RB = Bitpack_getu(instruction, width, lsb);
    assert(RB < 8);
    return RB;
}

/*
* Name: getRC
* Purpose: Get RC of instruction
* Input: A UM instruction
* Output: Returns RC code of instruction
*/
Um_register getRC(Um_instruction instruction)
{
    uint32_t width = 3;
    uint32_t lsb = 0;
    uint32_t RC = Bitpack_getu(instruction, width, lsb);
    assert(RC < 8);
    return RC;
}

/*
* Name: getVal
* Purpose: Get value of instruction
* Input: A UM instruction
* Output: Returns value of instruction
*/
Um_value getVal(Um_instruction instruction)
{
    uint32_t width = 25;
    uint32_t lsb = 0;
    uint32_t val = Bitpack_getu(instruction, width, lsb);
    return val;
}

/*
* Name: getLVRA
* Purpose: Get RA of load value instruction
* Input: A UM instruction
* Output: Returns RA code of load value instruction
*/
Um_opcode getLVRA(Um_instruction instruction)
{
    uint32_t width = 3;
    uint32_t lsb = 25;
    uint32_t RA = Bitpack_getu(instruction, width, lsb);
    assert(RA < 8);
    return RA;
}

/*
* Name: readWord
* Purpose: Reads in the information and packs it into a word
* Input: A file pointer to the input of instructions
* Output: Returns the bitpacked word
*/
Um_instruction readWord(FILE *input)
{
    assert(input != NULL);
    uint64_t word = 0;
    for (int i = 3; i >= 0; i--) {
        word = Bitpack_newu(word, 8, i * 8, (uint64_t)getc(input));
    }
    return word;
}