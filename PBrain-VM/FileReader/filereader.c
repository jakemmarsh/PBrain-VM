//
//  filereader.c
//  PBrain-VM
//
//  by Jake Marsh
//

// INCLUDE HEADER FILE
#include "filereader.h"

#include "../main.h"
#include "../API/api.h"

// INCLUDE NECESSARY LIBRARIES
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int i;

int open_file(const char * fileName) {
    int fp;
    
    fp = open(fileName, O_RDONLY);
    printf("Open is: %d\n", fp);
    
    // if error in read or EOF
    if (fp < 0) {
        printf("Bus Error 22\n");
        exit(0);
    }
    
    return fp;
}

void create_process(int i) {
    struct process *new_process = (struct process *)malloc(sizeof(struct process));
    
    new_process->BAR = i * 100;
    new_process->EAR = new_process->BAR;
    new_process->time_slice = rand() % 10 + 1;
    new_process->idNumber = i;
    new_process->next = NULL;
    
    if(ready_queue == NULL) {
        ready_queue = new_process;
    }
    else {
        get_last_rq()->next = new_process;
    }
    
    active_process = new_process;
}

void initialize_semaphores() {
    struct semaphore *blank = (struct semaphore *)malloc(sizeof(struct semaphore));
    blank->count = 1;
    blank->sem_queue = NULL;
    
    for(int i = 0; i < 10; i++) {
        SEM[i] = blank;
    }
}

void initialize_processes() {
    // loop through all ten files, opening them and reading into corresponding memory locations
    for(i = 0; i <= 9; i++) {
        char file_name[9];
        sprintf(file_name, "PC.%d.txt", i);
        
        program_line = i * 100;
        
        // create new process control block
        create_process(i);
        
        // call function to open the program file.
        // call will also check the return value
        fp = open_file(file_name);
        
        // read first line of source code into memory
        int ret = (int) read(fp, input_line, 7); //returns number of characters read
        
        // iterate through the rest of the source code
        while (ret > 0) {
            // write into memory
            for (j = 0; j < 6; j++) {
                read_to_memory(program_line, input_line, j);
            }
            
            //read in next line of code
            ret = (int) read(fp, input_line, 7);
            
            // increment current line count to keep track
            active_process->program_lines++;
            program_line++;
        }
    }
}