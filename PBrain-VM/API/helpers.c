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

char * get_named_param(int start_position) {
    char tempParam[2];
    
    memcpy(tempParam, &IR[start_position], 2);
    tempParam[2] = '\0';
    
    char* param = malloc(2);
    
    strcpy(param, tempParam);

    return param;
}

int get_int_param(int start_position, int length) {
    int i;
    
    int value = (int) (IR[start_position] - 48) * (pow(10, length-1));
    
    for (i = 1; i < length; i++) {
        value += (int) (IR[start_position + i] - 48) * (pow(10, length-(i+1)));
    }

    return value;
}