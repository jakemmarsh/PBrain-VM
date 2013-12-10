//
//  filereader.h
//  PBrain-VM
//
//  by Jake Marsh
//

// ONLY LOAD HEADER FILE ONCE
#ifndef FILE_READER_INCLUDED
#define FILE_READER_INCLUDED

struct process *old_process;

int open_file(const char * fileName);
void create_process(int i);
void initialize_semaphores();
int read_file(int program_number);
void initialize_processes();

#endif