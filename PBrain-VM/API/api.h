//
//  API.h
//  PBrain-VM
//
//  by Jake Marsh
//

// ONLY LOAD HEADER FILE ONCE
#ifndef FILE_READER_INCLUDED
#define FILE_READER_INCLUDED

void read_to_memory(int program_line, char input_line[7], int i);

void load_pointer_immediate(char pointer[2], int value);
void add_pointer_immediate(char pointer[2], int value);
void subtract_pointer_immediate(char pointer[2], int value);

void load_acc_immediate(int value);
void load_acc_register(char pointer[2]);
void load_acc_direct(int location);


void store_acc_register(char pointer [2]);

#endif