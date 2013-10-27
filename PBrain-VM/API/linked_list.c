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

struct process* get_prev(struct process *process_to_find_prev) {
    for(int i = 0; i <= 9; i++) {
        switch(i) {
            case 0: {
                if(PCB_0->next && PCB_0->next->idNumber == process_to_find_prev->idNumber) {
                    return PCB_0;
                }
                break;
            }
            case 1: {
                if(PCB_1->next && PCB_1->next->idNumber == process_to_find_prev->idNumber) {
                    return PCB_1;
                }
                break;
            }
            case 2: {
                if(PCB_2->next && PCB_2->next->idNumber == process_to_find_prev->idNumber) {
                    return PCB_2;
                }
                break;
            }
            case 3: {
                if(PCB_3->next && PCB_3->next->idNumber == process_to_find_prev->idNumber) {
                    return PCB_3;
                }
                break;
            }
            case 4: {
                if(PCB_4->next && PCB_4->next->idNumber == process_to_find_prev->idNumber) {
                    return PCB_4;
                }
                break;
            }
            case 5: {
                if(PCB_5->next && PCB_5->next->idNumber == process_to_find_prev->idNumber) {
                    return PCB_5;
                }
                break;
            }
            case 6: {
                if(PCB_6->next && PCB_6->next->idNumber == process_to_find_prev->idNumber) {
                    return PCB_6;
                }
                break;
            }
            case 7: {
                if(PCB_7->next && PCB_7->next->idNumber == process_to_find_prev->idNumber) {
                    return PCB_7;
                }
                break;
            }
            case 8: {
                if(PCB_8->next && PCB_8->next->idNumber == process_to_find_prev->idNumber) {
                    return PCB_8;
                }
                break;
            }
            case 9: {
                if(PCB_9->next && PCB_9->next->idNumber == process_to_find_prev->idNumber) {
                    return PCB_9;
                }
                break;
            }
            default: {
                break;
            }
        }
    }
    return NULL;
}

struct process* get_last() {
    for(int i = 0; i <= 9; i++) {
        switch(i) {
            case 0: {
                if(PCB_0->next == NULL) {
                    return PCB_0;
                }
                break;
            }
            case 1: {
                if(PCB_1->next == NULL) {
                    return PCB_1;
                }
                break;
            }
            case 2: {
                if(PCB_2->next == NULL) {
                    return PCB_2;
                }
                break;
            }
            case 3: {
                if(PCB_3->next == NULL) {
                    return PCB_3;
                }
                break;
            }
            case 4: {
                if(PCB_4->next == NULL) {
                    return PCB_4;
                }
                break;
            }
            case 5: {
                if(PCB_5->next == NULL) {
                    return PCB_5;
                }
                break;
            }
            case 6: {
                if(PCB_6->next == NULL) {
                    return PCB_6;
                }
                break;
            }
            case 7: {
                if(PCB_7->next == NULL) {
                    return PCB_7;
                }
                break;
            }
            case 8: {
                if(PCB_8->next == NULL) {
                    return PCB_8;
                }
                break;
            }
            case 9: {
                if(PCB_9->next == NULL) {
                    return PCB_9;
                }
                break;
            }
            default: {
                break;
            }
        }
    }
    return NULL;
}