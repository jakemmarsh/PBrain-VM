//
//  filereader.h
//  PBrain-VM
//
//  by Jake Marsh
//

// ONLY LOAD HEADER FILE ONCE
#ifndef FILE_READER_INCLUDED
#define FILE_READER_INCLUDED

int open_file(const char * fileName);
void create_process(int i, int n_size, int mem_locations);
void initialize_semaphores();
void read_file(int program_number);
void initialize_processes();

#endif