#pragma once

struct Process {
    unsigned int entry;
    unsigned int id;
    unsigned int instructions;
    unsigned int start;
    unsigned int end;
};

int initialize_log();
int LOG(char code[], char note[]);
struct Process** create_process(char filename[]);
char** tokenize(char line[]);
int get_len(char arr[]);
void copy_str(char* destination, char *source);
int to_number(char *str);
int is_digit(char ch);

