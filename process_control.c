/*
Tyler Gehring
CS240 Operating Systems
Bruce Bolden
4.11.24
*/

#include <stdio.h>

#include "process_control.h"
#include "operations.h"

void move(struct Process** process, struct Process** destination_queue){
    /*moves a process from inactive to active array. 
    Both arrays are designed to act as queues
    ARGS: pass reference to process pointer and pointer to array of pointers 
            Ex: move(&process[0], destination)
    */
    
    int dest_idx = find_back_queue(destination_queue);
    destination_queue[dest_idx] = *process;
    write_clock_time(*process);
    *process = NULL;
    LOG("Info", "Process Moved To destination Queue");
}

void print_queues(struct Process** inactive_processes, struct Process** active_processes){
    /*print the contents of each queue by process id and instructions left.*/
    printf("--------------------\n");
    printf("INACTIVE QUEUE:\n");
    printf("--------------------\n\n");
    for(int i = 0; i<MAX_PROCESSES; i++){
        if(inactive_processes[i] != NULL){
            printf("[%d] ID: %d | Instructions: %d | Entry:%d\n", 
                i, 
                inactive_processes[i]->id, 
                inactive_processes[i]->instructions,
                inactive_processes[i]->entry
            );
        }
    }

    printf("\n--------------------\n");
    printf("ACTIVE QUEUE:\n");
    printf("--------------------\n\n");
    for(int i = 0; i<MAX_PROCESSES; i++){
        if(active_processes[i] != NULL){
            printf("[%d] ID: %d | Instructions: %d | Entry:%d\n", 
                i, 
                active_processes[i]->id, 
                active_processes[i]->instructions,
                active_processes[i]->entry
            );
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


void execute(struct Process** active_processes, struct Process** inactive_processes, struct Process** final_processes){
    /*run instruction, check if process is done, check if process has been here for 5 calls, change execute idx if needed*/
    static int executions = 0;
    int queue_idx = find_front_queue(active_processes);

    active_processes[queue_idx]->instructions--;
    if(done(active_processes[queue_idx])){
        write_clock_time(active_processes[queue_idx]);
        int final_idx = find_back_queue(final_processes);
        final_processes[final_idx] = active_processes[queue_idx];
        active_processes[queue_idx] = NULL;
        LOG("Info", "Process finished");
        executions = 0;
    }
    else if (executions > 4){
        move(&active_processes[queue_idx], inactive_processes);
        executions = 0;
    }
    else{
        executions++;
    }
    increment_clock(1);
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

void write_clock_time(struct Process* process){
    /*if start time exists, write/overwrite exit time. if not the write start time*/
    if(process->start == -1){
        process->start = increment_clock(0);
    }
    else{
        process->end = increment_clock(0);
    }
   
}


void print_final_queues(struct Process** final_processes){
    printf("--------------------\n");
    printf("Final Processes:\n");
    printf("--------------------\n\n");
    for(int i = 0; i<MAX_PROCESSES; i++){
        if(final_processes[i] != NULL){
            printf("[%d] ID: %d | Instructions: %d | Entry: %d | Start: %d | End: %d\n", 
                i, 
                final_processes[i]->id, 
                final_processes[i]->instructions,
                final_processes[i]->entry,
                final_processes[i]->start,
                final_processes[i]->end
            );
        }
    }
}

void check_move(struct Process** inactive_processes, struct Process** active_processes, int clock){
    /*checks entry field in struct. if matches clock, move the process to active*/
    int i = 0;
    while(i<MAX_PROCESSES){
        if(inactive_processes[i]){
            if(inactive_processes[i]->entry <= clock){
                move(&inactive_processes[i], active_processes);
                break;
            }
        }
        i++;
    }
}
