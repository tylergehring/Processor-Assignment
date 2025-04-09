#include <stdio.h>

#include "process_control.h"
#include "operations.h"

int move(struct Process** source_queue, struct Process** destination_queue){
    /*moves a process from inactive to active array. Both arrays are designed to act as queues   
    0 is error val    
    */
    static int queue_idx = 0;
    if(source_queue[queue_idx] != NULL){
        destination_queue[queue_idx] = source_queue[queue_idx];
        source_queue[queue_idx] = NULL;
        queue_idx = ((queue_idx+1)%MAX_PROCESSES); //ensures queue loops to the top when max size is reached.
        LOG("Info", "Process Moved To destination Queue");
        return 1;
    }
    else{
        LOG("ERROR", "Process Couldn't Be Moved To destination Queue. source queue process == NULL");
        printf("ERROR:process_control::move. source_queue process == NULL");
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

int empty(struct Process** queue){
    /*returns 1 if queue is empty*/
    for(int i = 0; i<MAX_PROCESSES; i++){
        if(queue[i]!= NULL){
            return 0;
        }
    }
    return 1;
}


void execute(struct Process** active_processes, struct Process** inactive_processes){
    /*run instruction, check if process is done, check if process has been here for 5 calls, change execute idx if needed*/
    static int queue_idx = 0;
    static int executions = 0;
    if(active_processes[queue_idx]==NULL){
        int j;
        while(j !=10){
            if(active_processes[queue_idx] != NULL){
                break;
            }
            else{
                queue_idx = ((queue_idx+1)%MAX_PROCESSES);
            }
        }
    }
    else {
        active_processes[queue_idx]->instructions--;
        if(done(active_processes[queue_idx])){
            active_processes[queue_idx] = NULL;
            LOG("Info", "Process finished");
            queue_idx = ((queue_idx+1)%MAX_PROCESSES);
            executions = 0;
        }
        else if (executions > 4){
            move(active_processes, inactive_processes);
            queue_idx = ((queue_idx+1)%MAX_PROCESSES);
            executions = 0;
        }
        else{
            executions++;
        }
    }
}

int done(struct Process* process){
    /*returns 1 if process has no more instructions*/
    if(process->instructions<1){
        return 1;
    }
    return 0;
}

