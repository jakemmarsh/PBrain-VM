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
int fp, i, j, k;
char *ptr;
char input_line[7];

// These are variables representing the VM itself
char IR[6];

// PROGRAM MEMORY
char memory[1000][6];

int waiting_queue[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// to keep track of what we're doing
int opcode, program_line;

int main(int argc, const char * argv[]) {
    // use current time to generate random numbers, in order to be more "random"
    srand((unsigned)time(NULL));
    
    // make call to filereader to create all semaphores
    initialize_semaphores();
    
    // make call to filereader to open all files and initialize process blocks
    initialize_processes();
    
    // set active process to first one in the linked list
    active_process = ready_queue;

    // execute all code read in from source
    while (active_process->PC <= active_process->program_lines) {
        // if process has reached time slice, reset to zero, move to end of RQ, and start next process
        if(active_process->IC == active_process->time_slice) {
            switch_processes();
        }
        
        // copy current line into the instruction register (IR)
        int memory_address = get_memory_address(active_process, active_process->PC);
        for (k = 0; k < 6; k++) {
            IR[k] = memory[memory_address][k];
        }
        //printf("PC within main: %d\n", active_process->PC);
        //printf("memory address within main: %d\n", memory_address);
        // calculate integer equivalent of opcode chars
        opcode = (int) (IR[0] - 48) * 10;
        opcode += (int) (IR[1] - 48);
        
        printf("opcode is: %d\n", opcode);
        
        // make call to api to execute relevant function for opcode
        execute_opcode(opcode);
        
        active_process->IC++;
        active_process->PC++;
    }
}