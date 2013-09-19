//
//  API.c
//  PBrain-VM
//
//  by Jake Marsh
//

// INCLUDE HEADER FILE
#include "API.h"

void read_to_memory(char memory[100][6], int program_line, char input_line[7], int i) {
    memory[program_line][i] = input_line[i];
}