#include <stdio.h>

#include "operations.h"


int main(){
    initialize_log();
    LOG("Info", "Log Initialized");
    
    struct Process** inactive_processes = create_process("test3.txt");
    struct Process** active_processes = NULL;
    LOG("Info", "Queues Initialized");
    LOG("Info", "Processes Inactive");


    int idx = 0;
    while(1){
        if(!empty(inactive_processes)){
            start(inactive_processes[idx], active_processes);
            check_done(active_processes);
            check_timeout(active_processes);
            idx = ((idx+1)%10); //max size of 10
        }
        else{
            break;
        }
    }

    


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