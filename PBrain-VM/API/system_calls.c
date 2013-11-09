//
//  system_calls.c
//  PBrain-VM
//
//  by Jake Marsh
//

// INCLUDE NECESSARY LIBRARIES
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// INCLUDE HEADER FILE
#include "api.h"

// INCLUDE MAIN HEADER FILE TO ACCESS VARIABLES
#include "../main.h"

// SYSTEM CALL 00: GETPID
void system_getpid() {
    // place PID of calling process into register R0
    active_process->R0 = active_process->idNumber;
}

// SYSTEM CALL 01: WAIT
void system_wait(int pid, int sem_index) {
    // decrement semaphore at given index
    SEM[sem_index]->count -= 1;
    
    // if resulting count is < 0, process blocked and PCB placed at tail of semaphore's sem_queue
    if(SEM[sem_index]->count < 0) {
        remove_node_rq(active_process);
        get_last_sem_queue(SEM[sem_index])->next = active_process;
    }
    
    // if resulting count is >= 0, OS continues normally
    else if(SEM[sem_index]->count >= 0) {
    }
}

// SYSTEM CALL 02: SIGNAL
void system_signal(int pid, int sem_index) {
    // increment semaphore at given index
    SEM[sem_index]->count += 1;
    
    // if resulting count is <= 0, one or more processes are blocked and should be removed from the semaphore's queue and place at the tail of the ready queue
    if(SEM[sem_index]->count <= 0) {
        
    }
    // never blocks the caller
}