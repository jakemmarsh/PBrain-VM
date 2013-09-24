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

// INCLUDE FILES
#include "api.h"
#include "filereader.h"


// These variables are associated with the implementation of the VM
int fp;
char *ptr;
int i, j, k;
char input_line[7];

// These are variables representing the VM itself
char IR[6];
int PC = 0;

// POINTER REGISTERS
int P0, P1, P2, P3;

// GENERAL PURPOSE REGISTERS
int R0, R1, R2, R3;

int ACC;
char PSW[2];

// PROGRAM MEMORY
char memory[100][6];

// to keep track of what we're doing
int opcode;
int program_line = 0;

int main(int argc, const char * argv[])
{
    
    char *ptr;
    
    // call function to open the program file.
    // call will also check the return value
    fp = open_file("program.txt");
    
    // read first line of source code into memory
    int ret = (int) read(fp, input_line, 7 ); //returns number of characters read
    
    // iterate through the rest of the source code
    while (ret > 0) {
        ptr = input_line; //base address of array
        
        // write into Program_memory
        for (i = 0; i < 6; i++) {
            read_to_memory(program_line, input_line, i);
        }
        
        //read in next line of code
        ret = (int) read(fp, input_line, 7);
        
        // increment current line count to keep track
        program_line++;
    }

    // execute all code read in from source
    while (PC <= program_line)
    {
        
        // copy current line into the instruction register (IR)
        for (j = 0; j < 6; j++) {
            IR[j] = memory[PC][j];
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