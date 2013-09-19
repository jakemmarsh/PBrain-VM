//
//  main.c
//  PBrain-VM
//
//  by Jake Marsh
//

// INCLUDE NECESSARY LIBRARIES
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// INCLUDE FILES
#include "API.h"
#include "FileReader.h"


// These variables are associated with the implementation of the VM
int fp;
char *ptr;
int i;
int j, k;
char input_line [7];

// These are variables representing the VM itself
char IR[6];
int PC = 0;

// POINTER REGISTERS
int P0;
int P1;
int P2;
int P3;

// GENERAL PURPOSE REGISTERS
int R0;
int R1;
int R2;
int R3;

int ACC;
char PSW[2];

// PROGRAM MEMORY
char memory [100][6];

// to keep track of what we're doing
int opcode;
int program_line = 0;

int main(int argc, const char * argv[])
{
    
    char *ptr;
    
    // call function to open the program file.
    // call will also check the return value
    fp = openFile("program.txt", O_RDONLY);
    
    // read first line of source code into memory
    int ret = (int) read (fp, input_line, 7 ); //returns number of characters read
    
    // iterate through the rest of the source code
    while (1)
    {
        
        if (ret <= 0) //indicates end of file or
            break; //breaks out of loop
        
        ptr = input_line; //base address of array
        
        // write into Program_memory
        for (i = 0; i < 6; i++)
            memory[program_line][i] = input_line[i];
        
        //read in next line of code
        ret = (int) read (fp, input_line, 7 );
        
        // increment current line count to keep track
        program_line++;
    }
    
    // execute all code read in from source
    for (i = 0; i < program_line; i++)
        
    {
        
        // copy current line into the instruction register (IR)
        for (j = 0; j < 6; j++)
            IR[j] = memory[i] [j];
        
        // calculate integer equivalent of opcode chars
        opcode  = (int) (IR[0] -48) * 10;
        opcode += (int) (IR[1] -48);
        
        /* Now we know the opcode for the instruction. This
         provides all the information we need to parse the
         operands.
         */
        
        // execute relevant function for opcode

    }
}