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
    printf("wait. count: %d. sem index: %d\n", SEM[sem_index]->count, sem_index);
    
    // if resulting count is < 0, process blocked and PCB placed at tail of semaphore's sem_queue
    if(SEM[sem_index]->count < 0) {
        remove_node_rq(active_process);
        
        if(SEM[sem_index]->sem_queue) {
            get_last_sem_queue(SEM[sem_index])->next = active_process;
            struct process *temp_process = active_process;
            switch_processes();
            remove_node_rq(temp_process);
            // remove reference to next PCB on ready queue
            get_last_sem_queue(SEM[sem_index])->next = NULL;
        }
        else {
            SEM[sem_index]->sem_queue = active_process;
            struct process *temp_process = active_process;
            switch_processes();
            remove_node_rq(temp_process);
            // remove reference to next PCB on ready queue
            SEM[sem_index]->sem_queue->next = NULL;
        }
    }
    // if resulting count is >= 0, OS continues normally
}

// SYSTEM CALL 02: SIGNAL
void system_signal(int pid, int sem_index) {
    // increment semaphore at given index
    SEM[sem_index]->count += 1;
    printf("signal. count: %d. sem index: %d\n", SEM[sem_index]->count, sem_index);
    
    // if resulting count is <= 0, one or more processes are blocked and should be removed from the semaphore's queue and place at the tail of the ready queue
    if(SEM[sem_index]->count <= 0) {
        // place process at tail of the ready queue
        get_last_rq()->next = SEM[sem_index]->sem_queue;
        
        get_last_rq()->IC++;
        get_last_rq()->PC++;
        get_last_rq()->EAR = get_last_rq()->BAR + get_last_rq()->PC;
        
        // move sem_queue up one if there are additional processes in the queue
        if(get_prev_sem_queue(SEM[sem_index]->sem_queue->idNumber, SEM[sem_index])) {
            printf("get prev ID: %d\n", get_prev_sem_queue(SEM[sem_index]->sem_queue->idNumber, SEM[sem_index])->idNumber);
            printf("current ID: %d\n", SEM[sem_index]->sem_queue->idNumber);
            get_prev_sem_queue(SEM[sem_index]->sem_queue->idNumber, SEM[sem_index])->next = SEM[sem_index]->sem_queue->next;
        }
        // otherwise set sem_queue to null
        else {
            SEM[sem_index]->sem_queue = NULL;
        }
        
    }
    // never blocks the caller
}