//
//  FileReader.c
//  PBrain-VM
//
//  by Jake Marsh
//

// INCLUDE HEADER FILE
#include "FileReader.h"

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

void initialize_processes() {
    // loop through all ten files, opening them and reading into corresponding memory locations
    for(i = 0; i <= 9; i++) {
        char file_name[9];
        sprintf(file_name, "PC.%d.txt", i);
        
        program_line = i * 100;
        
        // set initial values for corresponding process control block
        switch(i) {
            case 0: {
                PCB_0 = (struct process *)malloc(sizeof(struct process));
                PCB_0->BAR = i * 100;
                PCB_0->EAR = PCB_0->BAR;
                PCB_0->time_slice = rand() % 10 + 1;
                PCB_0->idNumber = 0;
                active_process = PCB_0;
                break;
            }
            case 1: {
                PCB_1 = (struct process *)malloc(sizeof(struct process));
                PCB_1->BAR = i * 100;
                PCB_1->EAR = PCB_1->BAR;
                PCB_1->time_slice = rand() % 10 + 1;
                PCB_1->idNumber = 1;
                active_process = PCB_1;
                break;
            }
            case 2: {
                PCB_2 = (struct process *)malloc(sizeof(struct process));
                PCB_2->BAR = i * 100;
                PCB_2->EAR = PCB_2->BAR;
                PCB_2->time_slice = rand() % 10 + 1;
                PCB_2->idNumber = 2;
                active_process = PCB_2;
                break;
            }
            case 3: {
                PCB_3 = (struct process *)malloc(sizeof(struct process));
                PCB_3->BAR = i * 100;
                PCB_3->EAR = PCB_3->BAR;
                PCB_3->time_slice = rand() % 10 + 1;
                PCB_3->idNumber = 3;
                active_process = PCB_3;
                break;
            }
            case 4: {
                PCB_4 = (struct process *)malloc(sizeof(struct process));
                PCB_4->BAR = i * 100;
                PCB_4->EAR = PCB_4->BAR;
                PCB_4->time_slice = rand() % 10 + 1;
                PCB_4->idNumber = 4;
                active_process = PCB_4;
                break;
            }
            case 5: {
                PCB_5 = (struct process *)malloc(sizeof(struct process));
                PCB_5->BAR = i * 100;
                PCB_5->EAR = PCB_5->BAR;
                PCB_5->time_slice = rand() % 10 + 1;
                PCB_5->idNumber = 5;
                active_process = PCB_5;
                break;
            }
            case 6: {
                PCB_6 = (struct process *)malloc(sizeof(struct process));
                PCB_6->BAR = i * 100;
                PCB_6->EAR = PCB_6->BAR;
                PCB_6->time_slice = rand() % 10 + 1;
                PCB_6->idNumber = 6;
                active_process = PCB_6;
                break;
            }
            case 7: {
                PCB_7 = (struct process *)malloc(sizeof(struct process));
                PCB_7->BAR = i * 100;
                PCB_7->EAR = PCB_7->BAR;
                PCB_7->time_slice = rand() % 10 + 1;
                PCB_7->idNumber = 7;
                active_process = PCB_7;
                break;
            }
            case 8: {
                PCB_8 = (struct process *)malloc(sizeof(struct process));
                PCB_8->BAR = i * 100;
                PCB_8->EAR = PCB_8->BAR;
                PCB_8->time_slice = rand() % 10 + 1;
                PCB_8->idNumber = 8;
                active_process = PCB_8;
                break;
            }
            case 9: {
                PCB_9 = (struct process *)malloc(sizeof(struct process));
                PCB_9->BAR = i * 100;
                PCB_9->EAR = PCB_9->BAR;
                PCB_9->time_slice = rand() % 10 + 1;
                PCB_9->idNumber = 9;
                active_process = PCB_9;
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
    PCB_0->next = PCB_1;
    PCB_1->next = PCB_2;
    PCB_2->next = PCB_3;
    PCB_3->next = PCB_4;
    PCB_4->next = PCB_5;
    PCB_5->next = PCB_6;
    PCB_6->next = PCB_7;
    PCB_7->next = PCB_8;
    PCB_8->next = PCB_9;
    PCB_9->next = NULL;
}