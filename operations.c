#include <stdio.h>
#include <stdlib.h>

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
    fprintf(file, "%s | %s\n", code, note);
    fclose(file);
    return 0;
}

struct Process** create_process(char filename[]){
    /*creates an array that points to process structs. populates those structs by reading in data*/
    char buffer[200];
    char **tokens;
    struct Process** processes = (struct Process**)malloc(sizeof(struct Process*) * MAX_PROCESSES);
    if(processes == NULL){
        LOG("ERROR", "Could not allocate memory for struct Processes");
        exit(1);
    }

    FILE *fp = fopen(filename, "r");
    if (fp == NULL){
        LOG("ERROR", "Could not open file");
        exit(1);
    }

    int num_lines = 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL){
        struct Process* process = (struct Process*)malloc(sizeof(struct Process));
        if(process == NULL){
            LOG("ERROR", "Could not allocate memory for struct Process");
            exit(1);
        }
        tokens = tokenize(buffer);
        process->entry = to_number(tokens[0]);
        process->id = to_number(tokens[1]);
        process->instructions = to_number(tokens[2]);
        processes[num_lines] = process;
        num_lines++;
        LOG("Info", "Created Process");
    }
    fclose(fp);
    return processes;   
}

char** tokenize(char line[]){
    /*takes single line string and parses the txt into tokens*/
    LOG("Info", "Tokenizing..");
    char** tokens = (char**)malloc(sizeof(char*) * 3);
    char* t1 = (char*)malloc(sizeof(char)* MAX_TOKEN_SIZE);
    char* t2 = (char*)malloc(sizeof(char)* MAX_TOKEN_SIZE);
    char* t3 = (char*)malloc(sizeof(char)* MAX_TOKEN_SIZE);
    tokens[0] = t1;
    tokens[1] = t2;
    tokens[2] = t3;
    
    int buf_idx = 0;
    int token_num = 0;
    char buf[10];

    for(int i = 0; i<(get_len(line)+1); i++){
        if(is_digit(line[i])){
            buf[buf_idx] = line[i];
            buf_idx++;
        }
        else{
            buf[buf_idx] = '\0';

            if(token_num == 0){
                copy_str(t1, buf);
            }
            else if (token_num == 1){
                copy_str(t2, buf);
            }
            else if (token_num == 2){
                copy_str(t3, buf);
            }

            for(int j = 0; j<10; j++){
                buf[j] = '\0';
            }
            buf_idx = 0;
            token_num++;
        }
    }
    return tokens;
}

int get_len(char* arr){
    /*looks for Nul char and returns len when found*/
    int count = 0;
    while((arr[count]!= '\0')){
        count++;
    }

    return count;
}

void copy_str(char* destination, char* source){
    /*does not check size of either array*/
    for(int i = 0; i < get_len(source); i++){
        destination[i] = source[i];
    }
}


int to_number(char *str) {
    /*turns string of ints into an int*/
    int result = 0;
    for (int i=0; i< get_len(str); i++){
        result = result *10 + (str[i] - '0');
    }
    return result;
}


int is_digit(char ch) {
    return (ch >= '0' && ch <= '9');
}

void set_null(struct Process** queue){
    for(int i = 0; i<MAX_PROCESSES; i++){
        queue[i] = NULL;
    }
}