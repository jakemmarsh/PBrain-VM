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

// get the previous item in the ready queue, given a process ID as a parameter
struct process* get_prev_rq(int pid) {
    struct process *current_process = ready_queue;
    
    // search for process node whose "next" value has a pid that matches the parameter pid
    while(current_process->next) {
        if(current_process->next->idNumber == pid) {
            return current_process;
        }
        current_process = current_process->next;
    }
    
    return NULL;
}

// get the very last item in the ready queue
struct process* get_last_rq() {
    struct process *current_process = ready_queue;
    
    // loop through whole ready queue until there is no longer a "next" value
    while(current_process->next) {
        current_process = current_process->next;
    }
    
    return current_process;
}

// remove a node from the ready queue, given a process node as a parameter
void remove_node_rq(struct process* node) {
    // if there is a previous node, point its "next" to current node's "next"
    if(get_prev_rq(node->idNumber)) {
        get_prev_rq(node->idNumber)->next = node->next;
    }
}

// remove the very top of the ready queue
void remove_top_rq() {
    // set ready queue to ready queue's "next"
    ready_queue = ready_queue->next;
}

// get the previous item in the ready queue, given a process ID and a semaphore as parameters
struct process* get_prev_sem_queue(int pid, struct semaphore* semaphore) {
    struct process *current_process = semaphore->sem_queue;

    // search for process node whose "next" value has a pid that matches the parameter pid
    while(current_process->next) {
        if(current_process->next->idNumber == pid) {
            return current_process;
        }
        current_process = current_process->next;
    }
    
    return NULL;
}

// get the very last item in a semaphore queue, given a semaphore as a parameter
struct process* get_last_sem_queue(struct semaphore* semaphore) {
    struct process *current_process = semaphore->sem_queue;
    
    // loop through whole semaphore queue until there is no longer a "next" value
    while(current_process->next) {
        current_process = current_process->next;
    }
    return current_process;
}

// remove a node from a semaphore queue, given a process node and a semaphore as parameters
void remove_node_sem_queue(struct process* node, struct semaphore* semaphore) {
    // if there is a previous node, point its "next" to current node's "next"
    if(get_prev_sem_queue(node->idNumber, semaphore)) {
        get_prev_sem_queue(node->idNumber, semaphore)->next = node->next;
    }
}