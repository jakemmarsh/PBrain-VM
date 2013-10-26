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
    
    active_process = &PCB_0;
    
    // make call to filereader to open all files and initialize process blocks
    initialize_processes();

    // execute all code read in from source
    while (active_process->PC <= active_process->program_lines) {
        printf("PC: %d\n", active_process->PC);
        printf("lines in current process: %d\n", active_process->program_lines);
        
        // copy current line into the instruction register (IR)
        for (k = 0; k < 6; k++) {
            IR[k] = memory[active_process->PC + active_process->BAR][k];
        }
        
        // calculate integer equivalent of opcode chars
        opcode = (int) (IR[0] - 48) * 10;
        opcode += (int) (IR[1] - 48);
        
        printf("opcode is: %d\n", opcode);
        
        // make call to api to execute relevant function for opcode
        execute_opcode(opcode);
        
        active_process->PC++;
    }
}