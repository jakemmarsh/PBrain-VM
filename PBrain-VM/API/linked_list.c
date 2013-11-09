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
    struct process *next_node = ready_queue;
    
    while(next_node->next) {
        if(next_node->next->idNumber == pid) {
            return next_node;
        }
        next_node = next_node->next;
    }
    
    return NULL;
}

struct process* get_last_rq() {
    struct process *next_node = ready_queue;
    
    while(next_node->next) {
        next_node = next_node->next;
    }
    
    return next_node;
}

void remove_node_rq(struct process* node) {
    if(get_prev_rq(node->idNumber)) {
        get_prev_rq(node->idNumber)->next = node->next;
    }
}

struct process* get_prev_sem_queue(int pid, struct semaphore* semaphore) {
    struct process *next_node = semaphore->sem_queue;
    
    while(next_node->next) {
        if(next_node->next->idNumber == pid) {
            return next_node;
        }
        next_node = next_node->next;
    }
    
    return NULL;
}

struct process* get_last_sem_queue(struct semaphore* semaphore) {
    struct process *next_node = semaphore->sem_queue;
    
    while(next_node->next) {
        next_node = next_node->next;
    }
    
    return next_node;
}

void remove_node_sem_queue(struct process* node, struct semaphore* semaphore) {
    if(get_prev_sem_queue(node->idNumber, semaphore)) {
        get_prev_sem_queue(node->idNumber, semaphore)->next = node->next;
    }
}