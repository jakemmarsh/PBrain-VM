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

// INCLUDE MAIN HEADER AND FILEREADER HEADER FILES TO ACCESS VARIABLES
#include "../main.h"
#include "../FileReader/filereader.h"

// EXTRACT NAMED PARAM FROM AN INSTRUCTION, SUCH AS A POINTER OR REGISTER NAME
char * get_named_param(int start_position) {
    char tempParam[3];
    char* param;
    
    memcpy(tempParam, &IR[start_position], 2);
    tempParam[2] = '\0';
    
    param = malloc(2);
    
    strcpy(param, tempParam);

    return param;
}

// EXTRACT AN INTEGER PARAM FROM AN INSTRUCTION
int get_int_param(int start_position, int length) {
    int i,
    value = (int) (IR[start_position] - 48) * (pow(10, length-1));
    
    for (i = 1; i < length; i++) {
        value += (int) (IR[start_position + i] - 48) * (pow(10, length-(i+1)));
    }

    return value;
}

void switch_processes() {
    // release pages if process is exiting
    if(opcode == 99) {
        release_pages(active_process);
    }
    int k, opcode;
    // if a process still exists to complete
    if(active_process->next) {
        // print out data about old process that is stopping
        printf("\nOLD PROCESS ID: %d\n", active_process->idNumber);
        printf("OLD PROCESS TIME SLICE: %d\n", active_process->time_slice);
        printf("OLD PROCESS LAST INSTRUCTION: %s\n\n", IR);
        
        // set instruction counter back to zero
        active_process->IC = 0;
        
        get_last_rq()->next = active_process;
        
        struct process *temp_next = active_process->next;
        active_process->next = NULL;
        
        // switch to next process
        remove_node_rq(active_process);
        active_process = temp_next;
        ready_queue = active_process;
        
        // print out data about new process that is beginning
        printf("NEW PROCESS ID: %d\n", active_process->idNumber);
        printf("NEW PROCESS TIME SLICE: %d\n", active_process->time_slice);
        
        // copy current line into the instruction register (IR) for printing
        int memory_address = get_memory_address(active_process, active_process->PC);
        for (k = 0; k < 6; k++) {
            IR[k] = memory[memory_address][k];
        }
        printf("NEW PROCESS FIRST INSTRUCTION: %s\n\n", IR);
        opcode = (int) (IR[0] - 48) * 10;
        opcode += (int) (IR[1] - 48);
        if(opcode == 99 && !processes_remain()) {
            exit(0);
        }
        
        // set flag
        external_switch = 1;
    }
    else if(processes_remain()) {
        // search for files that still need to be read into memory
        for(int i = 0; i < 20; i++) {
            if(waiting_queue[i] == 1) {
                // switch to next process
                remove_node_rq(active_process);
                
                printf("\n");
                old_process = active_process;
                // only make changes if a new file was actually opened
                if(read_file(i)) {
                    // print out data about old process that is stopping
                    printf("OLD PROCESS ID: %d\n", old_process->idNumber);
                    printf("OLD PROCESS TIME SLICE: %d\n", old_process->time_slice);
                    printf("OLD PROCESS LAST INSTRUCTION: %s\n\n", IR);
                    
                    // reset old process
                    old_process->IC = 0;
                    get_last_rq()->next = old_process;
                    old_process->next = NULL;
                    
                    // change to new process
                    ready_queue = active_process;
                    
                    // reset flag
                    waiting_queue[i] = 0;
                    
                    // print out data about new process that is beginning
                    printf("NEW PROCESS ID: %d\n", active_process->idNumber);
                    printf("NEW PROCESS TIME SLICE: %d\n", active_process->time_slice);
                    int memory_address = get_memory_address(active_process, active_process->PC);
                    for (k = 0; k < 6; k++) {
                        IR[k] = memory[memory_address][k];
                    }
                    printf("NEW PROCESS FIRST INSTRUCTION: %s\n\n", IR);
                    opcode = (int) (IR[0] - 48) * 10;
                    opcode += (int) (IR[1] - 48);
                    
                    // set flag
                    external_switch = 1;
                }
                else {
                    printf("read file: %d\n", read_file(i));
                    // keep using same process if a new one was not successfully loaded
                    if(active_process->PC < active_process->program_lines) {
                        int memory_address = get_memory_address(active_process, active_process->PC);
                        for (k = 0; k < 6; k++) {
                            IR[k] = memory[memory_address][k];
                        }
                        opcode = (int) (IR[0] - 48) * 10;
                        opcode += (int) (IR[1] - 48);
                        
                        if(opcode != 99) {
                            active_process = old_process;
                            active_process->next = NULL;
                            ready_queue = active_process;
                        }
                        else {
                            int check = processes_remain();
                            printf("check: %d\n", check);
                            //halt();
                        }
                    }
                    else {
                        exit(0);
                    }
                }
                
                return;
            }
        }
    }
    // if no processes remain at all, print out data about old process that is stopping and exit
    else {
        printf("\nLAST PROCESS ID: %d\n", active_process->idNumber);
        printf("LAST PROCESS TIME SLICE: %d\n", active_process->time_slice);
        printf("LAST PROCESS LAST INSTRUCTION: %s\n\n", IR);
        
        exit(0);
    }
}

// find first available page in memory
int find_new_page() {
    for(int i = 0; i < 100; i++) {
        if(master_memory_table[i] == -1) {
            return i;
        }
    }
    return -1;
}

// find total number of pages that are available
int get_number_available_pages() {
    int count = 0;
    
    for(int i = 0; i < 100; i++) {
        if(master_memory_table[i] == -1) {
            count++;
        }
    }
    return count;
}

// calculate memory address from process' virtual address
int get_memory_address(struct process *p, int line) {
    int page = p->virtual_address[line][0],
    offset = p->virtual_address[line][1],
    memory_address = p->page_table[page]->base_address + offset;
    
    if(page == -1) {
        printf("That page number is invalid.\n");
        exit(0);
    }
    
    return memory_address;
}

// release all memory and pages held by a process
void release_pages(struct process *p) {
    // set page to available in master memory table
    for(int i = 0; i < 10; i++) {
        int page_base = p->page_table[i]->base_address;
        master_memory_table[page_base] = -1;
    }
    
    // overwrite contents of main memory previously used by process
    for(int i = 0; i < p->program_lines; i++) {
        int memory_address = get_memory_address(p, i);
        for(int j = 0; j < 6; j++) {
            memory[memory_address][j] = (char) 0;
        }
    }
}

int processes_remain() {
    for(int i = 0; i < 20; i++) {
        if(waiting_queue[i] == 1) {
            return 1;
        }
    }
    return 0;
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
        case 31: {
            mod(get_named_param(2), get_named_param(4));
            break;
        }
        case 32: {
            trap(get_int_param(2, 2), active_process->idNumber);
            break;
        }
        case 99: {
            halt();
            break;
        }
        default: {
            active_process;
            memory;
            master_memory_table;
            memory_address;
            printf("Invalid opcode: %d\n", opcode);
            break;
        }
    }
}