//
//  Main.h
//  PBrain-VM
//
//  by Jake Marsh
//

// ONLY LOAD HEADER FILE ONCE
#ifndef MAIN_INCLUDED
#define MAIN_INCLUDED

// These variables are associated with the implementation of the VM
extern int fp;
extern char input_line[7];

// These are variables representing the VM itself
extern char IR[6];

// PAGE TABLE ENTRY
struct page_table_entry {
    // BASE ADDRESS OF PAGE FRAME IN PHYSICAL MEMORY
    int base_address;
};

// PROCESS CONTROL BLOCK
struct process {
    struct process *next;
    // GENERAL PURPOSE REGISTERS
    int R0, R1, R2, R3,
    // POINTER REGISTERS
    P0, P1, P2, P3,
    // ACCUMULATOR
    ACC,
    // INSTRUCTION COUNTER
    IC,
    // TIME SLICE FOR PREEMPTING
    time_slice,
    // PROGRAM COUNTER
    PC,
    // TOTAL NUMBER OF LINES IN PROCESS'S PROGRAM
    program_lines,
    idNumber;
    char PSW[2];
    // PAGE TABLE
    struct page_table_entry *page_table[10];
    // 2D ARRAY TO GET MEMORY ADDRESS FROM VIRTUAL ADDRESS
    int virtual_address[100][2];
};

struct process *ready_queue, *active_process;

// SEMAPHORE
struct semaphore {
    int count;
    struct process *sem_queue;
};

struct semaphore *SEM[10];

int master_memory_table[100];

// PROGRAM MEMORY
extern char memory[1000][6];

// WAITING QUEUE
int waiting_queue[20];

// to keep track of what we're doing
extern int opcode;
extern int program_line;

#endif