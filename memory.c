/********************************************************************
* memory.c
* Assignment: UM (HW6)
* Authors: Yuehan (Eunice) Dai (ydai05), Grace Ye (gye01)
* Date: 11/23/21
* Summary: This is the implementation of memory, which
*          deals with all memory allocation and deallocation
********************************************************************/

#include "memory.h"

/*
* Name: newUM
* Purpose: Creates a new UM and initializes it
* Input: None
* Output: Returns the new UM
*/
UMachine newUM()
{
    UMachine newMachine;
    NEW(newMachine);
    uint32_t length = 8;
    uint32_t size = sizeof(uint32_t);
    /*Allocate and check for resource exhaustion by Mem_Failed exception*/
    newMachine->registers = UArray_new(length, size);
    newMachine->memory = Seq_new(0);
    newMachine->freeMemory =  Seq_new(0);
    
    newMachine->programCounter = 0;
    initializeRegisters(newMachine);
    return newMachine;
}

/*
* Name: initializeRegisters
* Purpose: Initializes all registers to 0
* Input: A UM
* Output: None, but all registers initialized
*/
void initializeRegisters(UMachine um)
{
    UArray_T registers = um->registers;
    for(int i = 0; i < 8; i ++){
        *(int *)UArray_at(registers, i) = 0;
    }
}

/*
* Name: freeMainMemory
* Purpose: Frees the main memory of the UM
* Input: A UM
* Output: None, but main memory freed
*/
void freeMainMemory(UMachine um)
{
    Seq_T mainMemory = um->memory;
    uint32_t length = Seq_length(mainMemory);
    for (uint32_t i = 0 ; i < length; i ++){
        freeSeg(um, i);
    }

    Seq_free(&(mainMemory));
}

/*
* Name: getRegVal
* Purpose: Gets a register value
* Input: A UM, an index from which to get the register value
* Output: Value at that given index of the register returned
*/
Um_value getRegVal(UMachine um, Um_register index)
{
    UArray_T registers = um->registers;
    return *(Um_value *)UArray_at(registers, index);
}

/*
* Name: setRegVal
* Purpose: Sets a register value
* Input: A UM, an index at which to set the register value, the value to set
* Output: Value at that given index of the register set to the provided value
*/
void setRegVal(UMachine um, Um_register index, Um_value val)
{
    UArray_T registers = um->registers;
    *(Um_value *)UArray_at(registers, index) = val;
}

/*
* Name: getSegVal
* Purpose: Gets a value within a given segment
* Input: A UM, the segment block, the index within the segment block
* Output: Returns value at that given segment at that given index within the
*         segment block
*/
Um_value getSegVal(UMachine um, uint32_t block, uint32_t index)
{
    Seq_T memory = um->memory;
    Um_value block_val = getRegVal(um, block);
    Um_value index_val = getRegVal(um, index);
    assert(block_val < (uint32_t)Seq_length(memory));

    UArray_T segment = Seq_get(memory, block_val);
    assert(segment != NULL);
    assert(index_val < (uint32_t)UArray_length(segment));

    return *(Um_value *)UArray_at(segment, index_val);
}

/*
* Name: getSeg
* Purpose: Gets value of a segment
* Input: A UM, the segment block
* Output: Returns value at that given segment
*/
UArray_T getSeg(UMachine um, uint32_t block)
{
    Seq_T memory = um->memory;
    Um_value block_val = getRegVal(um, block);
    assert(block_val < (uint32_t)Seq_length(memory));
    UArray_T segment = Seq_get(memory, block_val);
    return segment;
}

/*
* Name: setSegVal
* Purpose: Sets a value within a given segment
* Input: A UM, the segment block, the index within the segment block, 
*        the value to set
* Output: None, but sets value at that given segment at that given index 
*         within the segment block
*/
void setSegVal(UMachine um, uint32_t blockIndex, uint32_t index, Um_value val)
{
    Seq_T memory = um->memory;
    Um_value blockIndex_val = getRegVal(um, blockIndex);
    Um_value index_val = getRegVal(um, index);

    assert(blockIndex_val < (uint32_t)Seq_length(memory));

    UArray_T segment = Seq_get(memory, blockIndex_val);
    
    assert(segment != NULL);
    assert(index_val < (uint32_t)UArray_length(segment));
    *(Um_value *)UArray_at(segment, index_val) = val;
}

/*
* Name: setSeg
* Purpose: Sets value of a segment into a specific block
* Input: A UM, the block index, the segment
* Output: None, but sets value of segment into that specific block
*/
void setSeg(UMachine um, uint32_t blockIndex, UArray_T segment)
{
    Seq_T memory = um->memory;
    freeSeg(um, blockIndex);
    Seq_put(memory, blockIndex, segment);
}

/*
* Name: freeSeg
* Purpose: Frees a segment of main memory in the UM
* Input: A UM, the index
* Output: None, but frees segment at the specified index
*/
void freeSeg(UMachine um, uint32_t index)
{
    Seq_T memory = um->memory;
    UArray_T segment = (UArray_T)Seq_get(memory, index);
    if (segment != NULL){
        UArray_free(&segment);
    }
}