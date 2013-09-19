//
//  main.c
//  COS431-Project
//
//  Created by Jake Marsh
//

// INCLUDE NECESSARY LIBRARIES
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// INCLUDE FILES
#include "API.h"
#include "FileReader.h"


// These variables are associated with the implementation of the VM
int fp ;
char *ptr ;
int i ;
int j, k ;
char input_line [7] ;

// These are variables representing the VM itself
char IR[6] ;
int PC = 0 ;

// POINTER REGISTERS
int P0 ;
int P1 ;
int P2 ;
int P3 ;

// GENERAL PURPOSE REGISTERS
int R0 ;
int R1 ;
int R2 ;
int R3 ;

int ACC ;
char PSW[2] ;

// PROGRAM MEMORY
char memory [100][6]  ;

// to keep track of what we're doing
int opcode ;
int program_line = 0 ;

int main(int argc, const char * argv[])
{
    
    char *ptr ;
    fp = open("program.txt", O_RDONLY) ; //always check the return value.
    printf("Open is %d\n", fp) ;
    
    if (fp < 0) //error in read or EOF
    {printf("Bus Error 22\n") ;
        exit(0) ;
    }
    
    //iterate through the source code to and load it into memory
    
    int ret = read (fp, input_line, 7 ) ; //returns number of characters read
    int ret = (int) read (fp, input_line, 7 ) ; //returns number of characters read
    
    while (1)
    {
        
        if (ret <= 0) //indicates end of file or
            break ; //breaks out of loop
        ptr = input_line ; //base address of array
        
        //write into Program_memory
        
        for (i = 0; i < 6 ; i++)
            memory[program_line][i] = input_line[i] ;
        
        //read in next line of code
        
        ret = read (fp, input_line, 7 ) ;
        ret = (int) read (fp, input_line, 7 ) ;
        
        program_line++ ; //now at a new line in the program
    }
    
    
    /*We have read in the entire PBRAIN12 program.
     Now time to execute the code.
     First, we copy the current line of the program code
     into the Instruction Register (IR)
     */
    
    for (i = 0 ; i< program_line; i++)
        
    {
        
        for (j = 0 ; j < 6 ; j++)
            IR[j] = memory[i] [j] ;
        
        //get opcode and execute
        
        printf("Working on Program line %d\n", i) ;
        
        //easy way to calc integer equivalent of chars
        
        opcode  = (int) (IR[0] -48) * 10 ;
        opcode += (int) (IR[1] -48);
        
        /* Now we know the opcode for the instruction. This
         provides all the information we need to parse the
         operands.
         */
        
        printf("Opcode is %d\n", opcode) ;
    }
}