#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

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
    pid_t active_queue[200];
    pid_t inactive_queue[200];
    void* next_active_process = active_queue; //to create a queue like structure, pointer points to the next element in queue line and then loops to begining once it hits the end
    void* next_inactive_process = inactive_queue;
    LOG("Info", "Queues Initialized");

    LOG("Info", "Creating Process");
    pid_t pid = fork();
    if (pid < 0) {
        LOG("Error", "process did not fork properly");
        exit(-1); // Exit with error status
    } else if (pid == 0) {
        // Child process code
        LOG("Info", "child proccess is running..");
        printf("Child process: PID = %d\n", getpid());
        // Execute different code or use exec family functions to run a new program
        exit(0); // Exit child process
    } else {
        // Parent process code
        LOG("Info", "Parent process is finishing..");
        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);
        // Wait for the child process to finish (optional)
        // wait(NULL); 
    }

}