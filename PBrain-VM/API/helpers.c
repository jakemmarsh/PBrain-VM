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
#include "helpers.h"

// INCLUDE MAIN HEADER FILE TO ACCESS VARIABLES
#include "../main.h"

char * get_pointer_param(int start_position) {
    char tempPointer[2];
    
    memcpy(tempPointer, &IR[start_position], 2);
    tempPointer[2] = '\0';
    
    char* pointer = malloc(2);
    
    strcpy(pointer, tempPointer);

    return pointer;
}

int get_int_param(int start_position, int length) {
    int i;
    
    int value = (int) (IR[start_position] - 48) * (pow(10, length-1));
    
    for (i = 1; i < length; i++) {
        value += (int) (IR[start_position + i] - 48) * (pow(10, length-(i+1)));
    }

    return value;
}