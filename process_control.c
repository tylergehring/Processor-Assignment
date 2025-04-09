#include <stdio.h>

#include "process_control.h"
#include "operations.h"

int move(struct Process** inactive_processes, struct Process** active_processes){
    /*moves a process from inactive to active array. Both arrays are designed to act as queues
        0 is error val    
    */
    static int queue_idx = 0;
    if(inactive_processes[queue_idx] != NULL){
        active_processes[queue_idx] = inactive_processes[queue_idx];
        inactive_processes[queue_idx] = NULL;
        queue_idx = ((queue_idx+1)%MAX_PROCESSES); //ensures queue loops to the top when max size is reached.
        LOG("Info", "Process Moved To Active Queue");
        return 1;
    }
    else{
        LOG("ERROR", "Process Couldn't Be Moved To Active Queue. Inactive Process == NULL");
        printf("ERROR:process_control::move. Inactive process == NULL");
        return 0; 
    }
}

void print_queues(struct Process** inactive_processes, struct Process** active_processes){
    /*print the contents of each queue by process id and instructions left.*/
    LOG("Info", "Printing Queues");
    printf("--------------------\n");
    printf("INACTIVE QUEUE:\n");
    printf("--------------------\n\n");
    for(int i = 0; i<MAX_PROCESSES; i++){
        if(inactive_processes[i] != NULL){
            printf("[%d] I Process ID: %d | Instructions: %d\n", i, inactive_processes[i]->id, inactive_processes[i]->instructions);
        }
    }

    printf("\n--------------------\n");
    printf("ACTIVE QUEUE:\n");
    printf("--------------------\n\n");
    for(int i = 0; i<MAX_PROCESSES; i++){
        if(active_processes[i] != NULL){
            printf("[%d] A Process ID: %d | Instructions: %d\n", i, active_processes[i]->id, active_processes[i]->instructions);
        }
    }
}




