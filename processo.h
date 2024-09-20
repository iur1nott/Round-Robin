#ifndef PROCESSO_H
#define PROCESSO_H

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    PRONTO,
    EM_EXECUCAO,
    BLOQUEADO,
    CONCLUIDO
} ProcessState;

typedef struct {
    int id;
    int time_remaining;
    ProcessState state;
} Process;

Process* create_process(int id, int time_remaining);

void execute_process(Process* process);

#endif // PROCESSO_H