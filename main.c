#include <stdio.h>

#include "operations.h"


int main(){
    // To Do: 
    //        create proccesses
    //        create queues with rules
    //        Add them to inactive queue
    //        move them around
    initialize_log();
    LOG("Info", "Log Initialized");
    LOG("Info", "Creating Queues");
    
    
    
    
    LOG("Info", "Queues Initialized");

    LOG("Info", "Creating Process");
    struct Process** processes = create_process("test1.txt");
    printf("process Entry Time: %d\n", processes[0]->entry);
    printf("Process id: %d\n", processes[0]->id);
    printf("Process instructions: %d\n", processes[0]->instructions);
    //struct Process** p2 = create_process("test3.txt");
    //struct Process** p3 = create_process("test2.txt");


}