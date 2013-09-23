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
void store_acc_direct(int location);

void reg_to_mem_register(char register_name[2], char pointer[2]);
void reg_to_mem_direct(char register_name[2], int location);

void mem_to_reg_register(char register_name[2], char pointer[2]);
void mem_to_reg_direct(char register_name[2], int location);

void add_acc_immediate(int value);
void subtract_acc_immediate(int value);
void add_register_to_acc(char register_name[2]);
void subtract_register_from_acc(char register_name[2]);

void compare_greater_immediate(int value);
void compare_equal_immediate(int value);
void compare_lesser_immediate(int value);

void branch_if_true(int new_program_line);
void branch_if_false(int new_program_line);
void unconditional_branch(int new_program_line);

void acc_to_register(char register_name[2]);
void register_to_acc(char register_name[2]);

void halt();

#endif