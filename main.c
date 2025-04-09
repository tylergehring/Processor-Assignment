#include <stdio.h>
#include <stdlib.h>

#include "operations.h"
#include "process_control.h"


int main(){
    initialize_log();
    LOG("Info", "Log Initialized");
    
    struct Process** inactive_processes = create_process("test3.txt");
    struct Process** active_processes = (struct Process**)malloc(sizeof(struct Process*) * MAX_PROCESSES);
    set_null(active_processes);
    LOG("Info", "Queues Initialized");
    

    //print_queues(inactive_processes, active_processes);
    int success = 0;
    LOG("Info", "Moving Processes to active");
    success = move(inactive_processes, active_processes);
    move(inactive_processes, active_processes);
    print_queues(inactive_processes, active_processes);


/*
    int idx, count = 0;
    while(1){
        if(!empty(inactive_processes) && !empty(active_processes)){
            if ((count%2) == 0){
                move(inactive_processes[idx], active_processes);
            }
            execute(active_processes);
            check_done(active_processes);
            idx = ((idx+1)%10); //max size of 10
        }
        else{
            break;
        }
    }
*/
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