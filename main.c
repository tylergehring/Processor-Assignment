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
    set_null(inactive_processes);
    set_null(active_processes);
    if((inactive_processes == NULL) || (active_processes == NULL)){
        LOG("ERROR", "Could not allocate memory for struct Processes");
        printf("<ERROR IN QUEUE MEM ALLOCATION>\n");
        exit(1);
    }
    create_process(inactive_processes, "test3.txt");
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
            execute(active_processes, inactive_processes);
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
    printf("Success!!");

    //TO DO:
    // write empty, start, check_done, and check_timeout functions

    


    /*
    printf("process Entry Time: %d\n", processes[0]->entry);
    printf("Process id: %d\n", processes[0]->id);
    printf("Process instructions: %d\n\n", processes[0]->instructions);

    printf("process Entry Time: %d\n", processes[1]->entry);
    printf("Process id: %d\n", processes[1]->id);
    printf("Process instructions: %d\n\n", processes[1]->instructions);

    printf("process Entry Time: %d\n", processes[2]->entry);
    printf("Process id: %d\n", processes[2]->id);
    printf("Process instructions: %d\n\n", processes[2]->instructions);
    */
    //struct Process** p2 = create_process("test3.txt");
    //struct Process** p3 = create_process("test2.txt");


}