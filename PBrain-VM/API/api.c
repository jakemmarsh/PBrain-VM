//
//  API.c
//  PBrain-VM
//
//  by Jake Marsh
//

// INCLUDE NECESSARY LIBRARIES
#include <string.h>
#include <stdio.h>

// INCLUDE HEADER FILE
#include "API.h"

// INCLUDE MAIN HEADER FILE TO ACCESS VARIABLES
#include "../main.h"


// STORE LINE FROM PROGRAM INTO MEMORY
void read_to_memory(int program_line, char input_line[7], int i) {
    memory[program_line][i] = input_line[i];
}

// LOAD POINTER IMMEDIATE (00 Pn XX)
void load_pointer_immediate(char* pointer, int value) {
    // insert value into correct pointer variable
    if(!strcmp(pointer, "P0")) {
        P0 = value;
        return;
    }
    if(!strcmp(pointer, "P1")) {
        P1 = value;
        return;
    }
    if(!strcmp(pointer, "P2")) {
        P2 = value;
        return;
    }
    if(!strcmp(pointer, "P3")) {
        P3 = value;
        return;
    }
    
}

// ADD TO POINTER IMMEDIATE (01 Pn XX)
void add_pointer_immediate(char pointer[2], int value) {
    // increment correct pointer by value
    if(!strcmp(pointer, "P0")) {
        P0 += value;
        return;
    }
    if(!strcmp(pointer, "P1")) {
        P1 += value;
        return;
    }
    if(!strcmp(pointer, "P2")) {
        P2 += value;
        return;
    }
    if(!strcmp(pointer, "P3")) {
        P3 += value;
        return;
    }
}

// SUBTRACT FROM POINTER IMMEDIATE (02 Pn XX)
void subtract_pointer_immediate(char pointer[2], int value) {
    // decrement correct pointer by value
    if(!strcmp(pointer, "P0")) {
        P0 -= value;
        return;
    }
    if(!strcmp(pointer, "P1")) {
        P1 -= value;
        return;
    }
    if(!strcmp(pointer, "P2")) {
        P2 -= value;
        return;
    }
    if(!strcmp(pointer, "P3")) {
        P3 -= value;
        return;
    }
    
}

// LOAD ACCUMULATOR IMMEDIATE (03 XX XX)
void load_acc_immediate(int value) {
    ACC = value;
}

// LOAD ACCUMULATOR REGISTER ADDRESSING (04 Pn --)
void load_acc_register(char pointer[2]) {
    // set accumulator equal to memory location pointed to by pointer
    if(!strcmp(pointer, "P0")) {
        ACC = (int)memory[P0];
        return;
    }
    if(!strcmp(pointer, "P1")) {
        ACC = (int)memory[P1];
        return;
    }
    if(!strcmp(pointer, "P2")) {
        ACC = (int)memory[P2];
        return;
    }
    if(!strcmp(pointer, "P3")) {
        ACC = (int)memory[P3];
        return;
    }
}

// LOAD ACCUMULATOR DIRECT ADDRESSING (05 XX --)
void load_acc_direct(int location) {
    ACC = (int)memory[location];
}

// STORE ACCUMULATOR REGISTER ADDRESSING (06 Pn --)
void store_acc_register(char pointer [2]) {

}

// STORE ACCUMULATOR DIRECT ADDRESSING (07 XX --)
void store_acc_direct(char pointer[2]) {
    
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
void add_acc_immediate() {
    
}

// SUBTRACT ACCUMULATOR IMMEDIATE (13 XX XX)
void subtract_acc_immediate() {
    
}

// ADD CONTENTS OF REGISTER TO ACCUMULATOR (14 Rn --)
void add_register_to_acc() {
    
}

// SUBTRACT CONTENTS OF REGISTER FROM ACCUMULATOR (15 Rn --)
void subtract_register_from_acc() {
    
}

// ADD ACCUMULATOR REGISTER ADDRESSING (16 Pn --)
void add_acc_register() {
    
}

// ADD ACCUMULATOR DIRECT ADDRESSING (17 XX --)
void add_acc_direct() {
    
}

// SUBTRACT FROM ACCUMULATOR REGISTER ADDRESSING (18 Pn --)
void subtract_acc_register() {

}

// SUBTRACT FROM ACCUMULATOR DIRECT ADDRESSING (19 XX --)
void subtract_acc_direct() {
    
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
void acc_to_register() {
    
}

// STORE REGISTER TO ACCUMULATOR (30 Rn --)
void register_to_acc() {
    
}

// HALT (99 XX XX)
void halt() {
    
}