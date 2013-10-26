//
//  main.c
//  PBrain-VM
//
//  by Jake Marsh
//

// INCLUDE NECESSARY LIBRARIES
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>

// INCLUDE FILES
#include "main.h"
#include "API/api.h"
#include "FileReader/filereader.h"


// These variables are associated with the implementation of the VM
int fp;
char *ptr;
int i, j, k;
char input_line[7];

// These are variables representing the VM itself
char IR[6];
int PC = 0;

int R0, R1, R2, R3,
// POINTER REGISTERS
P0, P1, P2, P3,
// ACCUMULATOR
ACC;

char PSW[2];

// PROGRAM MEMORY
char memory[1000][6];

// to keep track of what we're doing
int opcode;
int program_line;

// PROCESS CONTROL BLOCKS
struct process PCB_0, PCB_1, PCB_2, PCB_3, PCB_4, PCB_5, PCB_6, PCB_7, PCB_8, PCB_9;

// keep track of current process for sending to instructions
struct process *active_process;

int main(int argc, const char * argv[]) {
    // use current time to generate random numbers, in order to be more "random"
    srand((unsigned)time(NULL));
    
    char *ptr;
    
    active_process = &PCB_0;
    
    // loop through all ten files, opening them and reading into corresponding memory locations
    for(i = 0; i <= 9; i++) {
        char file_name[9];
        sprintf(file_name, "PC.%d.txt", i);
        program_line = i * 100;
        
        // set base address register and time slice for corresponding process
        switch(i) {
            case 0: {
                PCB_0.BAR = i * 100;
                PCB_0.time_slice = rand() % 10 + 1;
                break;
            }
            case 1: {
                PCB_1.BAR = i * 100;
                PCB_1.time_slice = rand() % 10 + 1;
                break;
            }
            case 2: {
                PCB_2.BAR = i * 100;
                PCB_2.time_slice = rand() % 10 + 1;
                break;
            }
            case 3: {
                PCB_3.BAR = i * 100;
                PCB_3.time_slice = rand() % 10 + 1;
                break;
            }
            case 4: {
                PCB_4.BAR = i * 100;
                PCB_4.time_slice = rand() % 10 + 1;
                break;
            }
            case 5: {
                PCB_5.BAR = i * 100;
                PCB_5.time_slice = rand() % 10 + 1;
                break;
            }
            case 6: {
                PCB_6.BAR = i * 100;
                PCB_6.time_slice = rand() % 10 + 1;
                break;
            }
            case 7: {
                PCB_7.BAR = i * 100;
                PCB_7.time_slice = rand() % 10 + 1;
                break;
            }
            case 8: {
                PCB_8.BAR = i * 100;
                PCB_8.time_slice = rand() % 10 + 1;
                break;
            }
            case 9: {
                PCB_9.BAR = i * 100;
                PCB_9.time_slice = rand() % 10 + 1;
                break;
            }
            default: {
                printf("Invalid PCB id\n");
                break;
            }
        }
        
        // call function to open the program file.
        // call will also check the return value
        fp = open_file(file_name);
        
        // read first line of source code into memory
        int ret = (int) read(fp, input_line, 7 ); //returns number of characters read
        
        // iterate through the rest of the source code
        while (ret > 0) {
            ptr = input_line; //base address of array
            
            // write into memory
            for (j = 0; j < 6; j++) {
                read_to_memory(program_line, input_line, j);
            }
            
            //read in next line of code
            ret = (int) read(fp, input_line, 7);
            
            // increment current line count to keep track
            program_line++;
        }
    }

    // execute all code read in from source
    while (PC <= program_line) {
        printf("PC: %d\n", PC);
        printf("program_line: %d\n", program_line);
        
        // copy current line into the instruction register (IR)
        for (k = 0; k < 6; k++) {
            IR[k] = memory[PC][k];
        }
        
        // calculate integer equivalent of opcode chars
        opcode = (int) (IR[0] - 48) * 10;
        opcode += (int) (IR[1] - 48);
        
        printf("opcode is: %d\n", opcode);
        
        // execute relevant function for opcode
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
        PC++;

    }
}