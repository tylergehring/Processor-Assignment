#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //for sleep()

#include "operations.h"
#include "process_control.h"


int main(){
    // --- Initializing Logs ---
    initialize_log();
    LOG("Info", "Log Initialized");
    
    // --- Initializing Queues ---
    struct Process** inactive_processes = (struct Process**)malloc(sizeof(struct Process*) * MAX_PROCESSES);
    struct Process** active_processes = (struct Process**)malloc(sizeof(struct Process*) * MAX_PROCESSES);
    struct Process** final_processes = (struct Process**)malloc(sizeof(struct Process*) * MAX_PROCESSES);
    set_null(inactive_processes);
    set_null(active_processes);
    set_null(final_processes);
    if((inactive_processes == NULL) || (active_processes == NULL)){
        LOG("ERROR", "Could not allocate memory for struct Processes");
        printf("<ERROR IN QUEUE MEM ALLOCATION>\n");
        exit(1);
    }
    create_process(inactive_processes, "test2.txt");
    LOG("Info", "Queues Initialized");
    
    printf("################### Initial #########################\n");
    print_queues(inactive_processes, active_processes);

    int clock = 0;
    while(1){
        if(!empty(inactive_processes)){
            if ((clock%2) == 0){
                move(inactive_processes, active_processes); //move every 2 clock cycles
            }
        }
        if(!empty(active_processes)){
            LOG("Info", "Executing instruction");
            execute(active_processes, inactive_processes, final_processes);
        }

        if(empty(inactive_processes) && empty(active_processes)){
            break;
        }
        else{
            clock++;
            printf("################### Running #########################\n");
            print_queues(inactive_processes, active_processes);
            sleep(1);
        }
    }
    
    print_final_queues(final_processes);

    //TO DO:
    // write empty, start, check_done, and check_timeout functions

    
    /*
    move(inactive_processes, active_processes);
    move(inactive_processes, active_processes);
    
    printf("##########################\n");
    print_queues(inactive_processes, active_processes);
    */

}