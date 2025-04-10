#pragma once

#include "operations.h"

void move(struct Process** source_queue, struct Process** destination_queue);
void print_queues(struct Process** inactive_processes, struct Process** active_processes);
int empty(struct Process** queue);
void execute(struct Process** active_processes, struct Process** inactive_processes);
int done(struct Process* process);
int find_front_queue(struct Process** queue);
int find_back_queue(struct Process** queue);

