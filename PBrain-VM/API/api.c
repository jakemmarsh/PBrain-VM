//
//  API.c
//  PBrain-VM
//
//  by Jake Marsh
//

// INCLUDE HEADER FILE
#include "API.h"

// INCLUDE MAIN HEADER FILE TO ACCESS VARIABLES
#include "../main.h"


// STORE LINE FROM PROGRAM INTO MEMORY
void read_to_memory(int program_line, char input_line[7], int i) {
    memory[program_line][i] = input_line[i];
}

// LOAD POINTER IMMEDIATE (00 Pn XX)
void load_pointer_immediate() {
    
}

// ADD TO POINTER IMMEDIATE (01 Pn XX)
void add_pointer_immediate() {
    
}

// SUBTRACT FROM POINTER IMMEDIATE (02 Pn XX)
void subtract_pointer_immediate() {
    
}

// LOAD ACCUMULATOR IMMEDIATE (03 XX XX)
void load_ac_immediate() {
    
}

// LOAD ACCUMULATOR REGISTER ADDRESSING (04 Pn XX)
void load_ac_register() {
    
}

// LOAD ACCUMULATOR DIRECT ADDRESSING (05 XX --)
void load_ac_direct() {
    
}

// STORE ACCUMULATOR REGISTER ADDRESSING (06 Pn --)
void store_ac_register() {
    
}

// STORE ACCUMULATOR DIRECT ADDRESSING (07 XX --)
void store_ac_direct() {
    
}

// STORE REGISTER TO MEMORY: REGISTER ADDRESSING (08 Rn Pn)
void reg_to_mem_register() {
    
}

// STORE REGISTER TO MEMORY: DIRECT ADDRESSING (09 Rn XX)
void reg_to_mem_direct() {
    
}

// LOAD REGISTER FROM MEMORY: REGISTER ADDRESSING (10 Rn Pn)
void mem_to_reg_register() {
    
}

// LOAD REGISTER FROM MEMORY: DIRECT ADDRESSING (11 Rn XX)
void mem_to_reg_direct() {
    
}

// ADD ACCUMULATOR IMMEDIATE (12 XX XX)
void add_ac_immediate() {
    
}

// SUBTRACT ACCUMULATOR IMMEDIATE (13 XX XX)
void subtract_ac_immediate() {
    
}

// ADD CONTENTS OF REGISTER TO ACCUMULATOR (14 Rn --)
void add_register_to_ac() {
    
}

// SUBTRACT CONTENTS OF REGISTER FROM ACCUMULATOR (15 Rn --)
void subtract_register_from_ac() {
    
}

// ADD ACCUMULATOR REGISTER ADDRESSING (16 Pn --)
void add_ac_register() {
    
}

// ADD ACCUMULATOR DIRECT ADDRESSING (17 XX --)
void add_ac_direct() {
    
}

// SUBTRACT FROM ACCUMULATOR REGISTER ADDRESSING (18 Pn --)
void subtract_ac_register() {

}

// SUBTRACT FROM ACCUMULATOR DIRECT ADDRESSING (19 XX --)
void subtract_ac_direct() {
    
}

// COMPARE EQUAL REGISTER ADDRESSING (20 Pn --)
void compare_equal_register() {
    
}

// COMPARE LESS REGISTER ADDRESSING (21 Pn --)
void compare_less_register() {
    
}

// COMPARE GREATER REGISTER ADDRESSING (22 Pn --)
void compare_greater_register() {
    
}

// COMPARE GREATER IMMEDIATE (23 XX XX)
void compare_greater_immediate() {
    
}

// COMPARE EQUAL IMMEDIATE (24 XX XX)
void compare_equal_immediate() {
    
}

// COMPARE LESS IMMEDIATE (25 XX XX)
void compare_less_immediate() {
    
}

// TRUE BRANCH CONDITIONAL (26 XX --)
void branch_if_true() {
    
}

// FALSE BRANCH CONDITIONAL (27 XX --)
void branch_if_false() {
    
}

// BRANCH UNCONDITIONAL (28 XX --)
void unconditional_branch() {
    
}

// LOAD REGISTER FROM ACCUMULATOR (29 Rn --)
void ac_to_register() {
    
}

// STORE REGISTER TO ACCUMULATOR (30 Rn --)
void register_to_ac() {
    
}

// HALT (99 XX XX)
void halt() {
    
}