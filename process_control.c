#include <stdio.h>

#include "process_control.h"
#include "operations.h"

void move(struct Process** source_queue, struct Process** destination_queue){
    /*moves a process from inactive to active array. Both arrays are designed to act as queues*/
    int source_idx = find_front_queue(source_queue);
    int dest_idx  =find_back_queue(destination_queue);
    printf("SOURCE_IDX= %d. DEST_IDX= %d\n", source_idx, dest_idx);
    destination_queue[dest_idx] = source_queue[source_idx];
    source_queue[source_idx] = NULL;
    LOG("Info", "Process Moved To destination Queue");
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
    static int executions = 0;
    int queue_idx = find_front_queue(active_processes);

    active_processes[queue_idx]->instructions--;
    if(done(active_processes[queue_idx])){
        active_processes[queue_idx] = NULL;
        LOG("Info", "Process finished");
        executions = 0;
    }
    else if (executions > 4){
        move(active_processes, inactive_processes);
        executions = 0;
    }
    else{
        executions++;
    }
}

int done(struct Process* process){
    /*returns 1 if process has no more instructions*/
    if(process->instructions<1){
        return 1;
    }
    return 0;
}

int find_front_queue(struct Process** queue){
    /*finds first entry in queue*/
    int idx = 0;
    for(int i = 0; i<MAX_PROCESSES; i++){
        if(queue[i] != NULL){
            return idx;
        }
        else{
            idx++;
        }
    }
    return 0;
}

int find_back_queue(struct Process** queue){
    /*finds last entry in queue. returns open space*/
    int idx = MAX_PROCESSES-1;
    for(int i = (MAX_PROCESSES-1); i>-1; i--){
        if(queue[i] != NULL){
            return idx+1;
        }
        else{
            idx--;
        }
    }
    return 0;
}





/*
TO DO:
1. go back to last commit, then copy over your front and back queue functions
2. edit the code from where it worked to find your mistake.
active [0, N, 2, 3, 4, N, N]
inactive [N, 1, N, N, N, 5, N]

front_queue, inactvie should return 1;
back_queue, inactive should return 6

front_queue, active should return 0,
back_queue, active should return 5.

next active process will be placd at index 5. removed from indx 1 of inactive
*/