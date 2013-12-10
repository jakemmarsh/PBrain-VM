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
#include <time.h>

int approach = 1;

// open a text file
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

// takes an int (i) as a parameter. Creates a new process with all the corresponding values and places it on the ready queue
void create_process(int i) {
    struct process *new_process = (struct process *)malloc(sizeof(struct process));
    
    new_process->time_slice = rand() % 10 + 1;
    new_process->idNumber = i;
    new_process->next = NULL;
    
    // create all 10 page table entries for new process
    for(int i = 0; i < 10; i++) {
        struct page_table_entry *entry = (struct page_table_entry *)malloc(sizeof(struct page_table_entry));
        entry->base_address = -1; // -1 means invalid entry
        new_process->page_table[i] = entry;
    }
    
    // place new process in the ready queue
    if(ready_queue == NULL) {
        ready_queue = new_process;
    }
    else {
        get_last_rq()->next = new_process;
    }
    
    if(active_process) {
        old_process = active_process;
    }
    active_process = new_process;
}

// creates all 10 semaphores and places them in SEM, initialized with a count of 1
void initialize_semaphores() {
    int i;
    
    for(i = 0; i < 10; i++) {
        struct semaphore *blank = (struct semaphore *)malloc(sizeof(struct semaphore));
        blank->count = 1;
        blank->sem_queue = NULL;
        
        SEM[i] = blank;
    }
}

// open text file and read program into memory
int read_file(int program_number) {
    char file_name[15];
    int ret, i, j, n_size, mem_locations, page_address, page_number, starting_address;
    
    int return_value = 0;
    
    // raise flag and leave function if no pages left in memory
    if(find_new_page() == -1) {
        waiting_queue[program_number] = 1;
        return return_value;
    }
    // otherwise, open file and begin to read
    else {
        sprintf(file_name, "program_%d.txt", program_number);
        
        // call function to open the program file.
        // call will also check the return value
        fp = open_file(file_name);
        return_value = 1;
        
        // create new process control block
        create_process(program_number);
        
        // read first line of source code
        ret = (int) read(fp, input_line, 7); // returns number of characters read
        
        program_line = 0;
        
        // counter to keep track of what line is being read
        i = 0;
        
        page_number = -1;
        
        // iterate through the rest of the source code
        while (ret > 0) {
            // first line declares size of N
            if(i == 0) {
                // copy input line into IR to get integer from it
                for (j = 0; j < 6; j++) {
                    IR[j] = input_line[j];
                }
                
                // get size of N from IR
                n_size = get_int_param(2, 4);
            }
            // second line declares number of memory locations required
            else if(i == 1) {
                // copy input line into IR to get integer from it
                for (j = 0; j < 6; j++) {
                    IR[j] = input_line[j];
                }
                
                // get number of memory locations from IR
                mem_locations = get_int_param(2, 4);
                
                // leave function if not enough pages are available for process
                int pages_needed = 1 + ((mem_locations - 1) / 10); // ceiling
                if(pages_needed > get_number_available_pages()) {
                    waiting_queue[program_number] = 1;
                    // return failed flag
                    return_value = 0;
                    return return_value;
                }
            }
            // read body of program into memory
            else if(i > 1) {
                // if a new page is needed
                if(program_line % 10 == 0) {
                    // switch to new page
                    page_address = find_new_page();
                    starting_address = page_address;
                    program_line = starting_address;
                    
                    // mark page as occupied by process
                    master_memory_table[page_address] = program_number;
                    
                    page_number += 1;
                    active_process->page_table[page_number]->base_address = program_line;
                }
                
                // assign correct mapping from virtual to logical address
                active_process->virtual_address[active_process->program_lines][0] = page_number;
                active_process->virtual_address[active_process->program_lines][1] = active_process->program_lines % 10;
                
                // read line of program into memory
                for (j = 0; j < 6; j++) {
                    memory[program_line][j] = input_line[j];
                }
                
                // increment current line count to keep track
                active_process->program_lines++;
                program_line++;
            }
            
            //read in next line of code
            ret = (int) read(fp, input_line, 7);
            // increment counter
            i++;
        }
        
        // reserve necessary extra memory spaces beyond just program lines
        while(page_number * 10 < mem_locations) {
            // switch to new page
            page_address = find_new_page();
            starting_address = page_address;
            program_line = starting_address;
            
            // mark page as occupied by process
            master_memory_table[page_address] = program_number;
            
            page_number += 1;
            active_process->page_table[page_number]->base_address = program_line;
        }
        
        starting_address = page_address + 1;
    }
    
    return return_value;
}

void initialize_processes() {
    int i;
    
    // initialize master memory table
    for(i = 0; i < 100; i++) {
        master_memory_table[i] = -1; // -1 indicates an available page
    }
    
    // approach one: bring programs into memory in order (1-20)
    if(approach == 1) {
        // loop through all files, opening them and reading into corresponding memory locations
        for(i = 0; i < 20; i++) {
            read_file(i);
        }
    }
    // approach two: randomly pick files to open for a average turnaround time quicker than approach one
    else if(approach == 2) {
        int remaining_programs[20] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19},
        length = sizeof(remaining_programs)/sizeof(remaining_programs[0]),
        index,
        item;
        
        // use current time to generate random numbers, in order to be more "random"
        srand((unsigned)time(NULL));
        
        // randomly pick a file to open from array, and then remove corresponding number from array
        while(length > 0) {
            item = remaining_programs[rand() % length];
            
            // find the random integer within the array
            for(i = 0; i < length; i++) {
                if(remaining_programs[i] == item) {
                    index = i;
                }
            }
            
            // read file
            read_file(item);
            
            // move last item into place of read file
            remaining_programs[index] = remaining_programs[length - 1];
            
            // decrement size of array
            length--;
        }
    }
}