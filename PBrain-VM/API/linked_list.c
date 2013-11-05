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

struct process* get_prev(int pid) {
    struct process *next_node = ready_queue;
    
    while(next_node) {
        if(next_node->next->idNumber == pid) {
            return next_node;
        }
        next_node = next_node->next;
    }
    
    return NULL;
}

struct process* get_last() {
    struct process *next_node = ready_queue;
    
    while(next_node) {
        next_node = next_node->next;
    }
    
    return next_node;
}