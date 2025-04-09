#pragma once

#define MAX_PROCESSES 10 //max number of processes in a file.
#define MAX_TOKEN_SIZE 10 //max size of chars per token in file

struct Process {
    unsigned int entry;
    unsigned int id;
    unsigned int instructions;
    unsigned int start;
    unsigned int end;
};

int initialize_log();
int LOG(char code[], char note[]);
void create_process(struct Process** processes, char filename[]);
char** tokenize(char line[]);
int get_len(char arr[]);
void copy_str(char* destination, char *source);
int to_number(char *str);
int is_digit(char ch);
void set_null(struct Process** queue);

