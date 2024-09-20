#include <stdio.h>
#include <stdlib.h>
#include "processo.h"

// Function to create a new process
Process* create_process(int id, int time_remaining) {
    Process* process = (Process*)malloc(sizeof(Process));
    if (process == NULL) {
        fprintf(stderr, "Memory allocation failed for process.\n");
        exit(1);  // Handle memory allocation failure
    }
    process->id = id;
    process->time_remaining = time_remaining;
    process->state = PRONTO;
    return process;
}

// Function to simulate the execution of a process
void execute_process(Process* process) {
    if (process->state == PRONTO) {
        process->state = EM_EXECUCAO;
        printf("Process %d is now in execution (Time remaining: %d)\n", process->id, process->time_remaining);
        printf("Executing process %d (Time remaining: %d)\n", process->id, process->time_remaining);

        process->time_remaining--;  // Simulate the process execution by decreasing time
        process->state = PRONTO;

        if (process->time_remaining == 0) {
            process->state = CONCLUIDO;
            printf("Process %d completed.\n", process->id);
        }
    } else if (process->state == BLOQUEADO) {
        // Handle the process being blocked (no action in the current version)
    }
}