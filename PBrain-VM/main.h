//
//  Main.h
//  PBrain-VM
//
//  by Jake Marsh
//

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

// PROGRAM MEMORY
extern char memory[100][6];

// to keep track of what we're doing
extern int opcode;
extern int program_line;