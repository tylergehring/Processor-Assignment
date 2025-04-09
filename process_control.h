#pragma once

#include "operations.h"

int move(struct Process** inactive_process, struct Process** active_processes);
void print_queues(struct Process** inactive_processes, struct Process** active_processes);
int empty(struct Process** queue);
void execute(struct Process** active_processes, struct Process** inactive_processes);
int done(struct Process* process);

