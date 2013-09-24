//
//  helpers.c
//  PBrain-VM
//
//  by Jake Marsh
//

// INCLUDE NECESSARY LIBRARIES
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

// INCLUDE HEADER FILE
#include "api.h"

// INCLUDE MAIN HEADER FILE TO ACCESS VARIABLES
#include "../main.h"

// STORE LINE FROM PROGRAM INTO MEMORY
void read_to_memory(int program_line, char input_line[7], int i) {
    memory[program_line][i] = input_line[i];
}

// EXTRACT NAMED PARAM FROM AN INSTRUCTION, SUCH AS A POINTER OR REGISTER NAME
char * get_named_param(int start_position) {
    char tempParam[3];
    
    memcpy(tempParam, &IR[start_position], 2);
    tempParam[2] = '\0';
    
    char* param = malloc(2);
    
    strcpy(param, tempParam);

    return param;
}

// EXTRACT AN INTEGER PARAM FROM AN INSTRUCTION
int get_int_param(int start_position, int length) {
    int i;
    
    int value = (int) (IR[start_position] - 48) * (pow(10, length-1));
    
    for (i = 1; i < length; i++) {
        value += (int) (IR[start_position + i] - 48) * (pow(10, length-(i+1)));
    }

    return value;
}