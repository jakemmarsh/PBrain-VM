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
extern char *ptr;
extern int i, j, k;
extern char input_line[7];

// These are variables representing the VM itself
extern char IR[6];
extern int PC;

// POINTER REGISTERS
extern int P0, P1, P2, P3;

// GENERAL PURPOSE REGISTERS
extern int R0, R1, R2, R3;

extern int ACC;
extern char PSW[2];

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
    // BASE ADDRESS REGISTER
    BAR,
    // EFFECTIVE ADDRESS REGISTER (EAR = PC + BAR)
    EAR,
    // TIME SLICE FOR PREEMPTING
    time_slice;
    char PSW[2];
};

extern struct process PCB_0, PCB_1, PCB_2, PCB_3, PCB_4, PCB_5, PCB_6, PCB_7, PCB_8, PCB_9;

extern struct process *active_process;

// PROGRAM MEMORY
extern char memory[1000][6];

// to keep track of what we're doing
extern int opcode;
extern int program_line;

#endif