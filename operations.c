#include <stdio.h>

#include "operations.h"

int initialize_log(){
    FILE *file = fopen("operations.log", "w");
    if (file == NULL) { 
        perror("Error opening file"); 
        return -1; // Return an error code 
    } 
    //fprintf(file, "Log Initialized");
    fclose(file);
    return 0;
}

int LOG(char code[], char note[]){
    FILE *file = fopen("operations.log", "a"); 
    if (file == NULL) { 
        perror("Error opening file"); 
        return -1; // Return an error code 
    } 
    fprintf(file, "%s | %s\n\r", code, note);
    fclose(file);
    return 0;
}