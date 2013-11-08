//
//  API.h
//  PBrain-VM
//
//  by Jake Marsh
//

// ONLY LOAD HEADER FILE ONCE
#ifndef API_INCLUDED
#define API_INCLUDED

extern int external_switch;


// INSTRUCTION FUNCTIONS
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

void add_acc_register(char pointer[2]);
void add_acc_direct(int location);
void subtract_acc_register(char pointer[2]);
void subtract_acc_direct(int location);

void compare_equal_register(char pointer[2]);
void compare_lesser_register(char pointer[2]);
void compare_greater_register(char pointer[2]);

void compare_greater_immediate(int value);
void compare_equal_immediate(int value);
void compare_lesser_immediate(int value);

void branch_if_true(int new_program_line);
void branch_if_false(int new_program_line);
void unconditional_branch(int new_program_line);

void acc_to_register(char register_name[2]);
void register_to_acc(char register_name[2]);

void mod(char register_one[2], char register_two[2]);

void trap(int system_call, int pid);

void halt();

// SYSTEM CALL FUNCTIONS
void system_getpid();
void system_wait(int pid, int sem_index);
void system_signal(int pid, int sem_index);

// HELPER FUNCTIONS
void read_to_memory(int program_line, char input_line[7], int i);

char * get_named_param(int start_position);
int get_int_param(int start_position, int length);

void switch_processes();
void execute_opcode(int opcode);

// LINKED LIST FUNCTIONS
struct process* get_prev_rq(int pid);
struct process* get_last_rq();

#endif