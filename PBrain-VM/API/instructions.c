//
//  API.c
//  PBrain-VM
//
//  by Jake Marsh
//

// INCLUDE NECESSARY LIBRARIES
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// INCLUDE HEADER FILE
#include "api.h"

// INCLUDE MAIN HEADER FILE TO ACCESS VARIABLES
#include "../main.h"

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
        ACC = atoi(memory[P0]);
        return;
    }
    if(!strcmp(pointer, "P1")) {
        ACC = atoi(memory[P1]);
        return;
    }
    if(!strcmp(pointer, "P2")) {
        ACC = atoi(memory[P2]);
        return;
    }
    if(!strcmp(pointer, "P3")) {
        ACC = atoi(memory[P3]);
        return;
    }
}

// LOAD ACCUMULATOR DIRECT ADDRESSING (05 XX --)
void load_acc_direct(int location) {
    ACC = atoi(memory[location]);
}

// STORE ACCUMULATOR REGISTER ADDRESSING (06 Pn --)
void store_acc_register(char pointer[2]) {
    // convert ACC value to string
    char temp[7];
    sprintf(temp, "%d", ACC);
    
    // store accumulator in memory location pointed to by pointer
    if(!strcmp(pointer, "P0")) {
        strcpy(memory[P0], temp);
        return;
    }
    if(!strcmp(pointer, "P1")) {
        strcpy(memory[P1], temp);
        return;
    }
    if(!strcmp(pointer, "P2")) {
        strcpy(memory[P2], temp);
        return;
    }
    if(!strcmp(pointer, "P3")) {
        strcpy(memory[P3], temp);
        return;
    }
}

// STORE ACCUMULATOR DIRECT ADDRESSING (07 XX --)
void store_acc_direct(int location) {
    // convert ACC value to string
    char temp[7];
    sprintf(temp, "%d", ACC);
    
    // store accumulator in memory location specified
    strcpy(memory[location], temp);
}

// STORE REGISTER TO MEMORY: REGISTER ADDRESSING (08 Rn Pn)
void reg_to_mem_register(char register_name[2], char pointer[2]) {
    // convert specified register's value to string
    char temp[7];
    if(!strcmp(register_name, "R0")) {
        sprintf(temp, "%d", R0);
    }
    else if(!strcmp(register_name, "R1")) {
        sprintf(temp, "%d", R1);
    }
    else if(!strcmp(register_name, "R2")) {
        sprintf(temp, "%d", R2);
    }
    else if(!strcmp(register_name, "R3")) {
        sprintf(temp, "%d", R3);
    }
    
    // store converted value into memory location specified by pointer
    if(!strcmp(pointer, "P0")) {
        strcpy(memory[P0], temp);
        return;
    }
    if(!strcmp(pointer, "P1")) {
        strcpy(memory[P1], temp);
        return;
    }
    if(!strcmp(pointer, "P2")) {
        strcpy(memory[P2], temp);
        return;
    }
    if(!strcmp(pointer, "P3")) {
        strcpy(memory[P3], temp);
        return;
    }
}

// STORE REGISTER TO MEMORY: DIRECT ADDRESSING (09 Rn XX)
void reg_to_mem_direct(char register_name[2], int location) {
    // convert specified register's value to string
    char temp[7];
    if(!strcmp(register_name, "R0")) {
        sprintf(temp, "%d", R0);
    }
    else if(!strcmp(register_name, "R1")) {
        sprintf(temp, "%d", R1);
    }
    else if(!strcmp(register_name, "R2")) {
        sprintf(temp, "%d", R2);
    }
    else if(!strcmp(register_name, "R3")) {
        sprintf(temp, "%d", R3);
    }
    
    // store converted value into memory at specified location
    strcpy(memory[location], temp);
}

// LOAD REGISTER FROM MEMORY: REGISTER ADDRESSING (10 Rn Pn)
void mem_to_reg_register(char register_name[2], char pointer[2]) {
    int temp = 0;
    // get value from memory at location specified by pointer
    if(!strcmp(pointer, "P0")) {
        temp = atoi(memory[P0]);
    }
    else if(!strcmp(pointer, "P1")) {
        temp = atoi(memory[P1]);
    }
    else if(!strcmp(pointer, "P2")) {
        temp = atoi(memory[P2]);
    }
    else if(!strcmp(pointer, "P3")) {
        temp = atoi(memory[P3]);
    }
    
    // store value into specified register
    if(!strcmp(register_name, "R0")) {
        R0 = temp;
        return;
    }
    if(!strcmp(register_name, "R1")) {
        R1 = temp;
        return;
    }
    if(!strcmp(register_name, "R2")) {
        R2 = temp;
        return;
    }
    if(!strcmp(register_name, "R3")) {
        R3 = temp;
        return;
    }
}

// LOAD REGISTER FROM MEMORY: DIRECT ADDRESSING (11 Rn XX)
void mem_to_reg_direct(char register_name[2], int location) {
    // set register equal to memory location pointed to by pointer
    if(!strcmp(register_name, "R0")) {
        R0 = atoi(memory[location]);
        return;
    }
    if(!strcmp(register_name, "R1")) {
        R1 = atoi(memory[location]);
        return;
    }
    if(!strcmp(register_name, "R2")) {
        R2 = atoi(memory[location]);
        return;
    }
    if(!strcmp(register_name, "R3")) {
        R3 = atoi(memory[location]);
        return;
    }
}

// ADD ACCUMULATOR IMMEDIATE (12 XX XX)
void add_acc_immediate(int value) {
    ACC += value;
}

// SUBTRACT ACCUMULATOR IMMEDIATE (13 XX XX)
void subtract_acc_immediate(int value) {
    ACC -= value;
}

// ADD CONTENTS OF REGISTER TO ACCUMULATOR (14 Rn --)
void add_register_to_acc(char register_name[2]) {
    // add value from correct register
    if(!strcmp(register_name, "R0")) {
        ACC += R0;
        return;
    }
    if(!strcmp(register_name, "R1")) {
        ACC += R1;
        return;
    }
    if(!strcmp(register_name, "R2")) {
        ACC += R2;
        return;
    }
    if(!strcmp(register_name, "R3")) {
        ACC += R3;
        return;
    }
}

// SUBTRACT CONTENTS OF REGISTER FROM ACCUMULATOR (15 Rn --)
void subtract_register_from_acc(char register_name[2]) {
    // subtract value from correct register
    if(!strcmp(register_name, "R0")) {
        ACC -= R0;
        return;
    }
    if(!strcmp(register_name, "R1")) {
        ACC -= R1;
        return;
    }
    if(!strcmp(register_name, "R2")) {
        ACC -= R2;
        return;
    }
    if(!strcmp(register_name, "R3")) {
        ACC -= R3;
        return;
    }
}

// ADD ACCUMULATOR REGISTER ADDRESSING (16 Pn --)
void add_acc_register(char pointer[2]) {
    // increment ACC by data in memory at location specified by pointer
    if(!strcmp(pointer, "P0")) {
        ACC += atoi(memory[P0]);
        return;
    }
    if(!strcmp(pointer, "P1")) {
        ACC += atoi(memory[P1]);
        return;
    }
    if(!strcmp(pointer, "P2")) {
        ACC += atoi(memory[P2]);
        return;
    }
    if(!strcmp(pointer, "P3")) {
        ACC += atoi(memory[P3]);
        return;
    }
}

// ADD ACCUMULATOR DIRECT ADDRESSING (17 XX --)
void add_acc_direct(int location) {
    ACC += atoi(memory[location]);
}

// SUBTRACT FROM ACCUMULATOR REGISTER ADDRESSING (18 Pn --)
void subtract_acc_register(char pointer[2]) {
    // decrement ACC by data in memory at location specified by pointer
    if(!strcmp(pointer, "P0")) {
        ACC -= atoi(memory[P0]);
        return;
    }
    if(!strcmp(pointer, "P1")) {
        ACC -= atoi(memory[P1]);
        return;
    }
    if(!strcmp(pointer, "P2")) {
        ACC -= atoi(memory[P2]);
        return;
    }
    if(!strcmp(pointer, "P3")) {
        ACC -= atoi(memory[P3]);
        return;
    }
}

// SUBTRACT FROM ACCUMULATOR DIRECT ADDRESSING (19 XX --)
void subtract_acc_direct(int location) {
    ACC -= atoi(memory[location]);
}

// COMPARE EQUAL REGISTER ADDRESSING (20 Pn --)
void compare_equal_register(char pointer[2]) {
    int temp = 0;
    
    // get value from memory at location specified by pointer
    if(!strcmp(pointer, "P0")) {
        temp = atoi(memory[P0]);
    }
    else if(!strcmp(pointer, "P1")) {
        temp = atoi(memory[P1]);
    }
    else if(!strcmp(pointer, "P2")) {
        temp = atoi(memory[P2]);
    }
    else if(!strcmp(pointer, "P3")) {
        temp = atoi(memory[P3]);
    }
    
    // compare ACC to value retrieved from memory
    if(ACC == temp) {
        PSW[0] = 1;
    }
    else {
        PSW[0] = 0;
    }
}

// COMPARE LESS REGISTER ADDRESSING (21 Pn --)
void compare_lesser_register(char pointer[2]) {
    int temp = 0;
    
    // get value from memory at location specified by pointer
    if(!strcmp(pointer, "P0")) {
        temp = atoi(memory[P0]);
    }
    else if(!strcmp(pointer, "P1")) {
        temp = atoi(memory[P1]);
    }
    else if(!strcmp(pointer, "P2")) {
        temp = atoi(memory[P2]);
    }
    else if(!strcmp(pointer, "P3")) {
        temp = atoi(memory[P3]);
    }
    
    // compare ACC to value retrieved from memory
    if(ACC < temp) {
        PSW[0] = 1;
    }
    else {
        PSW[0] = 0;
    }
}

// COMPARE GREATER REGISTER ADDRESSING (22 Pn --)
void compare_greater_register(char pointer[2]) {
    int temp = 0;
    
    // get value from memory at location specified by pointer
    if(!strcmp(pointer, "P0")) {
        temp = atoi(memory[P0]);
    }
    else if(!strcmp(pointer, "P1")) {
        temp = atoi(memory[P1]);
    }
    else if(!strcmp(pointer, "P2")) {
        temp = atoi(memory[P2]);
    }
    else if(!strcmp(pointer, "P3")) {
        temp = atoi(memory[P3]);
    }
    
    // compare ACC to value retrieved from memory
    if(ACC > temp) {
        PSW[0] = 1;
    }
    else {
        PSW[0] = 0;
    }
}

// COMPARE GREATER IMMEDIATE (23 XX XX)
void compare_greater_immediate(int value) {
    if(ACC > value) {
        PSW[0] = 1;
    }
    else {
        PSW[0] = 0;
    }
}

// COMPARE EQUAL IMMEDIATE (24 XX XX)
void compare_equal_immediate(int value) {
    if(ACC == value) {
        PSW[0] = 1;
    }
    else {
        PSW[0] = 0;
    }
}

// COMPARE LESS IMMEDIATE (25 XX XX)
void compare_lesser_immediate(int value) {
    if(ACC < value) {
        PSW[0] = 1;
    }
    else {
        PSW[0] = 0;
    }
    
}

// TRUE BRANCH CONDITIONAL (26 XX --)
void branch_if_true(int new_program_line) {
    if(PSW[0] == 1) {
        PC = new_program_line;
    }
}

// FALSE BRANCH CONDITIONAL (27 XX --)
void branch_if_false(int new_program_line) {
    if(PSW[0] == 0) {
        PC = new_program_line;
    }
}

// BRANCH UNCONDITIONAL (28 XX --)
void unconditional_branch(int new_program_line) {
    PC = new_program_line;
}

// LOAD REGISTER FROM ACCUMULATOR (29 Rn --)
void acc_to_register(char register_name[2]) {
    // store ACC value to correct register
    if(!strcmp(register_name, "R0")) {
         R0 = ACC;
        return;
    }
    if(!strcmp(register_name, "R1")) {
        R1 = ACC;
        return;
    }
    if(!strcmp(register_name, "R2")) {
        R2 = ACC;
        return;
    }
    if(!strcmp(register_name, "R3")) {
        R3 = ACC;
        return;
    }
}

// STORE REGISTER TO ACCUMULATOR (30 Rn --)
void register_to_acc(char register_name[2]) {
    // get value to correct register
    if(!strcmp(register_name, "R0")) {
        ACC = R0;
        return;
    }
    if(!strcmp(register_name, "R1")) {
        ACC = R1;
        return;
    }
    if(!strcmp(register_name, "R2")) {
        ACC = R2;
        return;
    }
    if(!strcmp(register_name, "R3")) {
        ACC = R3;
        return;
    }
}

// HALT (99 XX XX)
void halt() {
    exit(0);
}