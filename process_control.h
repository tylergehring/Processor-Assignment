#pragma once

#include "operations.h"

int move(struct Process** inactive_process, struct Process** active_processes);
void print_queues(struct Process** inactive_processes, struct Process** active_processes);


