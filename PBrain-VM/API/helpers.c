//
//  helpers.c
//  PBrain-VM
//
//  by Jake Marsh
//

// INCLUDE NECESSARY LIBRARIES
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

// INCLUDE HEADER FILE
#include "api.h"

// INCLUDE MAIN HEADER FILE TO ACCESS VARIABLES
#include "../main.h"

// STORE LINE FROM PROGRAM INTO MEMORY
void read_to_memory(int program_line, char input_line[7], int i) {
    memory[program_line][i] = input_line[i];
}

// EXTRACT NAMED PARAM FROM AN INSTRUCTION, SUCH AS A POINTER OR REGISTER NAME
char * get_named_param(int start_position) {
    char tempParam[3];
    
    memcpy(tempParam, &IR[start_position], 2);
    tempParam[2] = '\0';
    
    char* param = malloc(2);
    
    strcpy(param, tempParam);

    return param;
}

// EXTRACT AN INTEGER PARAM FROM AN INSTRUCTION
int get_int_param(int start_position, int length) {
    int i;
    
    int value = (int) (IR[start_position] - 48) * (pow(10, length-1));
    
    for (i = 1; i < length; i++) {
        value += (int) (IR[start_position + i] - 48) * (pow(10, length-(i+1)));
    }

    return value;
}

void switch_processes() {
    // print out data about old process that is stopping
    printf("\nOLD PROCESS ID: %d\n", active_process->idNumber);
    printf("OLD PROCESS TIME SLICE: %d\n", active_process->time_slice);
    printf("OLD PROCESS LAST INSTRUCTION: %s\n\n", IR);
    
    // set instruction counter back to zero
    active_process->IC = 0;
    
    // set previous item in linked list to link to current item's "next"
    if(get_prev(active_process)) {
        get_prev(active_process)->next = active_process->next;
    }
    
    // set last item in linked list to link to current item
    get_last()->next = active_process;
    // set current item's "next" to null since it is now at the end
    struct process *tempNext = active_process->next;
    active_process->next = NULL;
    // change active process to old "next" value
    active_process = tempNext;
    
    // print out data about new process that is beginning
    printf("NEW PROCESS ID: %d\n", active_process->idNumber);
    printf("NEW PROCESS TIME SLICE: %d\n", active_process->time_slice);
    // copy current line into the instruction register (IR) for printing
    for (k = 0; k < 6; k++) {
        IR[k] = memory[active_process->EAR][k];
    }
    printf("NEW PROCESS FIRST INSTRUCTION: %s\n\n", IR);
}

void execute_opcode(int opcode) {
    switch(opcode) {
        case 0: {
            load_pointer_immediate(get_named_param(2), get_int_param(4, 2));
            break;
        }
        case 1: {
            add_pointer_immediate(get_named_param(2), get_int_param(4, 2));
            break;
        }
        case 2: {
            subtract_pointer_immediate(get_named_param(2), get_int_param(4, 2));
            break;
        }
        case 3: {
            load_acc_immediate(get_int_param(2, 4));
            break;
        }
        case 4: {
            load_acc_register(get_named_param(2));
            break;
        }
        case 5: {
            load_acc_direct(get_int_param(2, 2));
            break;
        }
        case 6: {
            store_acc_register(get_named_param(2));
            break;
        }
        case 7: {
            store_acc_direct(get_int_param(2, 2));
            break;
        }
        case 8: {
            reg_to_mem_register(get_named_param(2), get_named_param(4));
            break;
        }
        case 9: {
            reg_to_mem_direct(get_named_param(2), get_int_param(4, 2));
            break;
        }
        case 10: {
            mem_to_reg_register(get_named_param(2), get_named_param(4));
            break;
        }
        case 11: {
            mem_to_reg_direct(get_named_param(2), get_int_param(4, 2));
            break;
        }
        case 12: {
            add_acc_immediate(get_int_param(2, 4));
            break;
        }
        case 13: {
            subtract_acc_immediate(get_int_param(2, 4));
            break;
        }
        case 14: {
            add_register_to_acc(get_named_param(2));
            break;
        }
        case 15: {
            subtract_register_from_acc(get_named_param(2));
            break;
        }
        case 16: {
            add_acc_register(get_named_param(2));
            break;
        }
        case 17: {
            add_acc_direct(get_int_param(2, 2));
            break;
        }
        case 18: {
            subtract_acc_register(get_named_param(2));
            break;
        }
        case 19: {
            subtract_acc_direct(get_int_param(2, 2));
            break;
        }
        case 20: {
            compare_equal_register(get_named_param(2));
            break;
        }
        case 21: {
            compare_lesser_register(get_named_param(2));
            break;
        }
        case 22: {
            compare_greater_register(get_named_param(2));
            break;
        }
        case 23: {
            compare_greater_immediate(get_int_param(2, 4));
            break;
        }
        case 24: {
            compare_equal_immediate(get_int_param(2, 4));
            break;
        }
        case 25: {
            compare_lesser_immediate(get_int_param(2, 4));
            break;
        }
        case 26: {
            branch_if_true(get_int_param(2, 2));
            break;
        }
        case 27: {
            branch_if_false(get_int_param(2, 2));
            break;
        }
        case 28: {
            unconditional_branch(get_int_param(2, 2));
            break;
        }
        case 29: {
            acc_to_register(get_named_param(2));
            break;
        }
        case 30: {
            register_to_acc(get_named_param(2));
            break;
        }
        case 99: {
            halt();
            break;
        }
        default: {
            printf("Invalid opcode\n");
            break;
        }
    }
}