#pragma once

#include "operations.h"


void move(struct Process** process, struct Process** destination_queue);
void print_queues(struct Process** inactive_processes, struct Process** active_processes);
int empty(struct Process** queue);
void execute(struct Process** active_processes, struct Process** inactive_processes, struct Process** final_processes);
int done(struct Process* process);
int find_front_queue(struct Process** queue);
int find_back_queue(struct Process** queue);
void write_clock_time(struct Process* process);
void print_final_queues(struct Process** final_processes);
void check_move(struct Process** inactive_processes, struct Process** active_processes, int clock);

