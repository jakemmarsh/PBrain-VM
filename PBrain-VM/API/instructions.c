//
//  instructions.c
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
        active_process->P0 = value;
        return;
    }
    if(!strcmp(pointer, "P1")) {
        active_process->P1 = value;
        return;
    }
    if(!strcmp(pointer, "P2")) {
        active_process->P2 = value;
        return;
    }
    if(!strcmp(pointer, "P3")) {
        active_process->P3 = value;
        return;
    }
    
}

// ADD TO POINTER IMMEDIATE (01 Pn XX)
void add_pointer_immediate(char pointer[2], int value) {
    // increment correct pointer by value
    if(!strcmp(pointer, "P0")) {
        active_process->P0 += value;
        return;
    }
    if(!strcmp(pointer, "P1")) {
        active_process->P1 += value;
        return;
    }
    if(!strcmp(pointer, "P2")) {
        active_process->P2 += value;
        return;
    }
    if(!strcmp(pointer, "P3")) {
        active_process->P3 += value;
        return;
    }
}

// SUBTRACT FROM POINTER IMMEDIATE (02 Pn XX)
void subtract_pointer_immediate(char pointer[2], int value) {
    // decrement correct pointer by value
    if(!strcmp(pointer, "P0")) {
        active_process->P0 -= value;
        return;
    }
    if(!strcmp(pointer, "P1")) {
        active_process->P1 -= value;
        return;
    }
    if(!strcmp(pointer, "P2")) {
        active_process->P2 -= value;
        return;
    }
    if(!strcmp(pointer, "P3")) {
        active_process->P3 -= value;
        return;
    }
    
}

// LOAD ACCUMULATOR IMMEDIATE (03 XX XX)
void load_acc_immediate(int value) {
    active_process->ACC = value;
}

// LOAD ACCUMULATOR REGISTER ADDRESSING (04 Pn --)
void load_acc_register(char pointer[2]) {
    // set accumulator equal to memory location pointed to by pointer
    if(!strcmp(pointer, "P0")) {
        active_process->ACC = atoi(memory[get_memory_address(active_process, active_process->P0)]);
        return;
    }
    if(!strcmp(pointer, "P1")) {
        active_process->ACC = atoi(memory[get_memory_address(active_process, active_process->P1)]);
        return;
    }
    if(!strcmp(pointer, "P2")) {
        active_process->ACC = atoi(memory[get_memory_address(active_process, active_process->P2)]);
        return;
    }
    if(!strcmp(pointer, "P3")) {
        active_process->ACC = atoi(memory[get_memory_address(active_process, active_process->P3)]);
        return;
    }
}

// LOAD ACCUMULATOR DIRECT ADDRESSING (05 XX --)
void load_acc_direct(int location) {
    active_process->ACC = atoi(memory[get_memory_address(active_process, location)]);
}

// STORE ACCUMULATOR REGISTER ADDRESSING (06 Pn --)
void store_acc_register(char pointer[2]) {
    // convert ACC value to string
    char temp[7];
    sprintf(temp, "%d", active_process->ACC);
    
    // store accumulator in memory location pointed to by pointer
    if(!strcmp(pointer, "P0")) {
        strcpy(memory[get_memory_address(active_process, active_process->P0)], temp);
        return;
    }
    if(!strcmp(pointer, "P1")) {
        strcpy(memory[get_memory_address(active_process, active_process->P1)], temp);
        return;
    }
    if(!strcmp(pointer, "P2")) {
        strcpy(memory[get_memory_address(active_process, active_process->P2)], temp);
        return;
    }
    if(!strcmp(pointer, "P3")) {
        strcpy(memory[get_memory_address(active_process, active_process->P3)], temp);
        return;
    }
}

// STORE ACCUMULATOR DIRECT ADDRESSING (07 XX --)
void store_acc_direct(int location) {
    // convert ACC value to string
    char temp[7];
    sprintf(temp, "%d", active_process->ACC);
    
    // store accumulator in memory location specified
    strcpy(memory[get_memory_address(active_process, location)], temp);
}

// STORE REGISTER TO MEMORY: REGISTER ADDRESSING (08 Rn Pn)
void reg_to_mem_register(char register_name[2], char pointer[2]) {
    // convert specified register's value to string
    char temp[7];
    if(!strcmp(register_name, "R0")) {
        sprintf(temp, "%d", active_process->R0);
    }
    else if(!strcmp(register_name, "R1")) {
        sprintf(temp, "%d", active_process->R1);
    }
    else if(!strcmp(register_name, "R2")) {
        sprintf(temp, "%d", active_process->R2);
    }
    else if(!strcmp(register_name, "R3")) {
        sprintf(temp, "%d", active_process->R3);
    }
    
    // store converted value into memory location specified by pointer
    if(!strcmp(pointer, "P0")) {
        strcpy(memory[get_memory_address(active_process, active_process->P0)], temp);
        return;
    }
    if(!strcmp(pointer, "P1")) {
        strcpy(memory[get_memory_address(active_process, active_process->P1)], temp);
        return;
    }
    if(!strcmp(pointer, "P2")) {
        strcpy(memory[get_memory_address(active_process, active_process->P2)], temp);
        return;
    }
    if(!strcmp(pointer, "P3")) {
        strcpy(memory[get_memory_address(active_process, active_process->P3)], temp);
        return;
    }
}

// STORE REGISTER TO MEMORY: DIRECT ADDRESSING (09 Rn XX)
void reg_to_mem_direct(char register_name[2], int location) {
    // convert specified register's value to string
    char temp[7];
    if(!strcmp(register_name, "R0")) {
        sprintf(temp, "%d", active_process->R0);
    }
    else if(!strcmp(register_name, "R1")) {
        sprintf(temp, "%d", active_process->R1);
    }
    else if(!strcmp(register_name, "R2")) {
        sprintf(temp, "%d", active_process->R2);
    }
    else if(!strcmp(register_name, "R3")) {
        sprintf(temp, "%d", active_process->R3);
    }
    
    // store converted value into memory at specified location
    strcpy(memory[get_memory_address(active_process, location)], temp);
}

// LOAD REGISTER FROM MEMORY: REGISTER ADDRESSING (10 Rn Pn)
void mem_to_reg_register(char register_name[2], char pointer[2]) {
    int temp = 0;
    // get value from memory at location specified by pointer
    if(!strcmp(pointer, "P0")) {
        temp = atoi(memory[get_memory_address(active_process, active_process->P0)]);
    }
    else if(!strcmp(pointer, "P1")) {
        temp = atoi(memory[get_memory_address(active_process, active_process->P1)]);
    }
    else if(!strcmp(pointer, "P2")) {
        temp = atoi(memory[get_memory_address(active_process, active_process->P2)]);
    }
    else if(!strcmp(pointer, "P3")) {
        temp = atoi(memory[get_memory_address(active_process, active_process->P3)]);
    }
    
    // store value into specified register
    if(!strcmp(register_name, "R0")) {
        active_process->R0 = temp;
        return;
    }
    if(!strcmp(register_name, "R1")) {
        active_process->R1 = temp;
        return;
    }
    if(!strcmp(register_name, "R2")) {
        active_process->R2 = temp;
        return;
    }
    if(!strcmp(register_name, "R3")) {
        active_process->R3 = temp;
        return;
    }
}

// LOAD REGISTER FROM MEMORY: DIRECT ADDRESSING (11 Rn XX)
void mem_to_reg_direct(char register_name[2], int location) {
    // set register equal to memory location pointed to by pointer
    if(!strcmp(register_name, "R0")) {
        active_process->R0 = atoi(memory[get_memory_address(active_process, location)]);
        return;
    }
    if(!strcmp(register_name, "R1")) {
        active_process->R1 = atoi(memory[get_memory_address(active_process, location)]);
        return;
    }
    if(!strcmp(register_name, "R2")) {
        active_process->R2 = atoi(memory[get_memory_address(active_process, location)]);
        return;
    }
    if(!strcmp(register_name, "R3")) {
        active_process->R3 = atoi(memory[get_memory_address(active_process, location)]);
        return;
    }
}

// ADD ACCUMULATOR IMMEDIATE (12 XX XX)
void add_acc_immediate(int value) {
    active_process->ACC += value;
}

// SUBTRACT ACCUMULATOR IMMEDIATE (13 XX XX)
void subtract_acc_immediate(int value) {
    active_process->ACC -= value;
}

// ADD CONTENTS OF REGISTER TO ACCUMULATOR (14 Rn --)
void add_register_to_acc(char register_name[2]) {
    // add value from correct register
    if(!strcmp(register_name, "R0")) {
        active_process->ACC += active_process->R0;
        return;
    }
    if(!strcmp(register_name, "R1")) {
        active_process->ACC += active_process->R1;
        return;
    }
    if(!strcmp(register_name, "R2")) {
        active_process->ACC += active_process->R2;
        return;
    }
    if(!strcmp(register_name, "R3")) {
        active_process->ACC += active_process->R3;
        return;
    }
}

// SUBTRACT CONTENTS OF REGISTER FROM ACCUMULATOR (15 Rn --)
void subtract_register_from_acc(char register_name[2]) {
    // subtract value from correct register
    if(!strcmp(register_name, "R0")) {
        active_process->ACC -= active_process->R0;
        return;
    }
    if(!strcmp(register_name, "R1")) {
        active_process->ACC -= active_process->R1;
        return;
    }
    if(!strcmp(register_name, "R2")) {
        active_process->ACC -= active_process->R2;
        return;
    }
    if(!strcmp(register_name, "R3")) {
        active_process->ACC -= active_process->R3;
        return;
    }
}

// ADD ACCUMULATOR REGISTER ADDRESSING (16 Pn --)
void add_acc_register(char pointer[2]) {
    // increment ACC by data in memory at location specified by pointer
    if(!strcmp(pointer, "P0")) {
        active_process->ACC += atoi(memory[get_memory_address(active_process, active_process->P0)]);
        return;
    }
    if(!strcmp(pointer, "P1")) {
        active_process->ACC += atoi(memory[get_memory_address(active_process, active_process->P1)]);
        return;
    }
    if(!strcmp(pointer, "P2")) {
        active_process->ACC += atoi(memory[get_memory_address(active_process, active_process->P2)]);
        return;
    }
    if(!strcmp(pointer, "P3")) {
        active_process->ACC += atoi(memory[get_memory_address(active_process, active_process->P3)]);
        return;
    }
}

// ADD ACCUMULATOR DIRECT ADDRESSING (17 XX --)
void add_acc_direct(int location) {
    active_process->ACC += atoi(memory[get_memory_address(active_process, location)]);
}

// SUBTRACT FROM ACCUMULATOR REGISTER ADDRESSING (18 Pn --)
void subtract_acc_register(char pointer[2]) {
    // decrement ACC by data in memory at location specified by pointer
    if(!strcmp(pointer, "P0")) {
        active_process->ACC -= atoi(memory[get_memory_address(active_process, active_process->P0)]);
        return;
    }
    if(!strcmp(pointer, "P1")) {
        active_process->ACC -= atoi(memory[get_memory_address(active_process, active_process->P1)]);
        return;
    }
    if(!strcmp(pointer, "P2")) {
        active_process->ACC -= atoi(memory[get_memory_address(active_process, active_process->P2)]);
        return;
    }
    if(!strcmp(pointer, "P3")) {
        active_process->ACC -= atoi(memory[get_memory_address(active_process, active_process->P3)]);
        return;
    }
}

// SUBTRACT FROM ACCUMULATOR DIRECT ADDRESSING (19 XX --)
void subtract_acc_direct(int location) {
    active_process->ACC -= atoi(memory[get_memory_address(active_process, location)]);
}

// COMPARE EQUAL REGISTER ADDRESSING (20 Pn --)
void compare_equal_register(char pointer[2]) {
    int temp = 0;
    
    // get value from memory at location specified by pointer
    if(!strcmp(pointer, "P0")) {
        temp = atoi(memory[get_memory_address(active_process, active_process->P0)]);
    }
    else if(!strcmp(pointer, "P1")) {
        temp = atoi(memory[get_memory_address(active_process, active_process->P1)]);
    }
    else if(!strcmp(pointer, "P2")) {
        temp = atoi(memory[get_memory_address(active_process, active_process->P2)]);
    }
    else if(!strcmp(pointer, "P3")) {
        temp = atoi(memory[get_memory_address(active_process, active_process->P3)]);
    }
    
    // compare ACC to value retrieved from memory
    if(active_process->ACC == temp) {
        active_process->PSW[0] = 1;
    }
    else {
        active_process->PSW[0] = 0;
    }
}

// COMPARE LESS REGISTER ADDRESSING (21 Pn --)
void compare_lesser_register(char pointer[2]) {
    int temp = 0;
    
    // get value from memory at location specified by pointer
    if(!strcmp(pointer, "P0")) {
        temp = atoi(memory[get_memory_address(active_process, active_process->P0)]);
    }
    else if(!strcmp(pointer, "P1")) {
        temp = atoi(memory[get_memory_address(active_process, active_process->P1)]);
    }
    else if(!strcmp(pointer, "P2")) {
        temp = atoi(memory[get_memory_address(active_process, active_process->P2)]);
    }
    else if(!strcmp(pointer, "P3")) {
        temp = atoi(memory[get_memory_address(active_process, active_process->P3)]);
    }
    
    // compare ACC to value retrieved from memory
    if(active_process->ACC < temp) {
        active_process->PSW[0] = 1;
    }
    else {
        active_process->PSW[0] = 0;
    }
}

// COMPARE GREATER REGISTER ADDRESSING (22 Pn --)
void compare_greater_register(char pointer[2]) {
    int temp = 0;
    
    // get value from memory at location specified by pointer
    if(!strcmp(pointer, "P0")) {
        temp = atoi(memory[get_memory_address(active_process, active_process->P0)]);
    }
    else if(!strcmp(pointer, "P1")) {
        temp = atoi(memory[get_memory_address(active_process, active_process->P1)]);
    }
    else if(!strcmp(pointer, "P2")) {
        temp = atoi(memory[get_memory_address(active_process, active_process->P2)]);
    }
    else if(!strcmp(pointer, "P3")) {
        temp = atoi(memory[get_memory_address(active_process, active_process->P3)]);
    }
    
    // compare ACC to value retrieved from memory
    if(active_process->ACC > temp) {
        active_process->PSW[0] = 1;
    }
    else {
        active_process->PSW[0] = 0;
    }
}

// COMPARE GREATER IMMEDIATE (23 XX XX)
void compare_greater_immediate(int value) {
    if(active_process->ACC > value) {
        active_process->PSW[0] = 1;
    }
    else {
        active_process->PSW[0] = 0;
    }
}

// COMPARE EQUAL IMMEDIATE (24 XX XX)
void compare_equal_immediate(int value) {
    if(active_process->ACC == value) {
        active_process->PSW[0] = 1;
    }
    else {
        active_process->PSW[0] = 0;
    }
}

// COMPARE LESS IMMEDIATE (25 XX XX)
void compare_lesser_immediate(int value) {
    if(active_process->ACC < value) {
        active_process->PSW[0] = 1;
    }
    else {
        active_process->PSW[0] = 0;
    }
    
}

// TRUE BRANCH CONDITIONAL (26 XX --)
void branch_if_true(int new_program_line) {
    if(active_process->PSW[0] == 1) {
        // have to subtract one to account for line numbers starting at 0, not 1
        active_process->PC = new_program_line - 1;
    }
}

// FALSE BRANCH CONDITIONAL (27 XX --)
void branch_if_false(int new_program_line) {
    if(active_process->PSW[0] == 0) {
        // have to subtract one to account for line numbers starting at 0, not 1
        active_process->PC = new_program_line - 1;
    }
}

// BRANCH UNCONDITIONAL (28 XX --)
void unconditional_branch(int new_program_line) {
    // have to subtract one to account for line numbers starting at 0, not 1
    active_process->PC = new_program_line - 1;
}

// LOAD REGISTER FROM ACCUMULATOR (29 Rn --)
void acc_to_register(char register_name[2]) {
    // store ACC value to correct register
    if(!strcmp(register_name, "R0")) {
         active_process->R0 = active_process->ACC;
        return;
    }
    if(!strcmp(register_name, "R1")) {
        active_process->R1 = active_process->ACC;
        return;
    }
    if(!strcmp(register_name, "R2")) {
        active_process->R2 = active_process->ACC;
        return;
    }
    if(!strcmp(register_name, "R3")) {
        active_process->R3 = active_process->ACC;
        return;
    }
}

// STORE REGISTER TO ACCUMULATOR (30 Rn --)
void register_to_acc(char register_name[2]) {
    // get value to correct register
    if(!strcmp(register_name, "R0")) {
        active_process->ACC = active_process->R0;
        return;
    }
    if(!strcmp(register_name, "R1")) {
        active_process->ACC = active_process->R1;
        return;
    }
    if(!strcmp(register_name, "R2")) {
        active_process->ACC = active_process->R2;
        return;
    }
    if(!strcmp(register_name, "R3")) {
        active_process->ACC = active_process->R3;
        return;
    }
}

// MOD INSTRUCTION (31 Rn Rn)
void mod(char register_one[2], char register_two[2]) {
    int temp_one, temp_two;
    
    // get value from correct first register
    if(!strcmp(register_one, "R0")) {
        temp_one = active_process->R0;
    }
    if(!strcmp(register_one, "R1")) {
        temp_one = active_process->R1;
    }
    if(!strcmp(register_one, "R2")) {
        temp_one = active_process->R2;
    }
    if(!strcmp(register_one, "R3")) {
        temp_one = active_process->R3;
    }
    
    // get value from correct second register
    if(!strcmp(register_two, "R0")) {
        temp_two = active_process->R0;
    }
    if(!strcmp(register_two, "R1")) {
        temp_two = active_process->R1;
    }
    if(!strcmp(register_two, "R2")) {
        temp_two = active_process->R2;
    }
    if(!strcmp(register_two, "R3")) {
        temp_two = active_process->R3;
    }
    
    // store result value
    active_process->ACC = temp_one % temp_two;
}

// REQUEST A SYSTEM CALL (32 XX XX)
void trap(int system_call, int pid) {
    switch(system_call) {
        case 0: {
            system_getpid();
            break;
        }
        case 1: {
            system_wait(pid, active_process->R0);
            break;
        }
        case 2: {
            system_signal(pid, active_process->R0);
            break;
        }
        default: {
            printf("Invalid system call: %d\n", system_call);
            break;
        }
    }
}

// HALT (99 XX XX)
void halt() {
    // free memory used by active process before switching
    release_pages(active_process);
    
    // set previous item in linked list to link to current item's "next"
    remove_top_rq();
    switch_processes();
}