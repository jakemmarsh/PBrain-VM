//
//  linked_list.c
//  PBrain-VM
//
//  by Jake Marsh
//

// INCLUDE NECESSARY LIBRARIES
#include <stdlib.h>

// INCLUDE HEADER FILE
#include "api.h"

// INCLUDE MAIN HEADER FILE TO ACCESS VARIABLES
#include "../main.h"

struct process* get_prev_rq(int pid) {
    struct process *current_process = ready_queue;
    
    while(current_process->next) {
        if(current_process->next->idNumber == pid) {
            return current_process;
        }
        current_process = current_process->next;
    }
    
    return NULL;
}

struct process* get_last_rq() {
    struct process *current_process = ready_queue;
    
    while(current_process->next) {
        current_process = current_process->next;
    }
    
    return current_process;
}

void remove_node_rq(struct process* node) {
    if(get_prev_rq(node->idNumber)) {
        get_prev_rq(node->idNumber)->next = node->next;
    }
}

struct process* get_prev_sem_queue(int pid, struct semaphore* semaphore) {
    struct process *current_process = semaphore->sem_queue;
    
    while(current_process->next) {
        if(current_process->next->idNumber == pid) {
            return current_process;
        }
        current_process = current_process->next;
    }
    
    return NULL;
}

struct process* get_last_sem_queue(struct semaphore* semaphore) {
    struct process *current_process = semaphore->sem_queue;
    
    printf("current process id: %d\n", current_process->idNumber);
    while(current_process->next) {
        current_process = current_process->next;
    }
    
    return current_process;
}

void remove_node_sem_queue(struct process* node, struct semaphore* semaphore) {
    if(get_prev_sem_queue(node->idNumber, semaphore)) {
        get_prev_sem_queue(node->idNumber, semaphore)->next = node->next;
    }
}