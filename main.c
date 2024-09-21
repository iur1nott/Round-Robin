#include <stdio.h>
#include <stdlib.h>

typedef enum {
    PRONTO,
    EM_EXECUCAO,
    BLOQUEADO,
    CONCLUIDO
} ProcessState;

// Estrutura para representar um processo
typedef struct {
    int id;
    int time_remaining;
    ProcessState state;
} Process;

char* return_state_string(int estado) {
    char *str;
    switch (estado) {
        case PRONTO:
            str ="PRONTO";
            break;
        case EM_EXECUCAO:
            str ="EM EXECUÇÃO";
            break;
        case BLOQUEADO:
            str ="BLOQUEADO";
            break;
        case CONCLUIDO:
            str ="CONCLUIDO";
            break;
        default:
            str ="INCOGNOSCÍVEL";
    }
    return str;
}

// Função auxiliar para mostrar processos
void mostrar_processos(Process processes[], int num_processes) {
    printf("Processos:\n");
    for (int j = 0; j < num_processes; j++) {
        printf("\tProcesso %d: %s\n", processes[j].id,return_state_string(processes[j].state));
    }
}

void round_robin(Process processes[], int num_processes, int quantum) {
    int current_time = 0;

    // Criando variável para checar processos pendentes
    int concluido = 0;
    while (!concluido) {
        // Loop para iterar por cada processo
        concluido = 1;
        for (int i = 0; i < num_processes; i++) {
            if (processes[i].state == PRONTO) {
                processes[i].state = EM_EXECUCAO;
            } else {
                continue;
            }

            mostrar_processos(processes,num_processes);

            // Estabelecendo limite a partir da soma do tempo atual com o quantum
            int limite = current_time+quantum;
            while (current_time < limite) {
                // Verificando se o processo ainda não foi concluido
                if (processes[i].time_remaining > 0) {
                    printf("Tempo %d: executando processo %d (%ds para conclusão)\n", current_time, processes[i].id, processes[i].time_remaining);
                    current_time++;
                    processes[i].time_remaining--;
                } else {
                    // Em caso de conclusão de processo (time_remaining = 0)
                    processes[i].state = CONCLUIDO;
                    printf("Tempo %d: processo %d concluído\n", current_time, processes[i].id);
                    current_time++;
                    break;
                }
            }

            if (processes[i].state != CONCLUIDO) {
                printf("Tempo %d: processo %d sofreu preempção\n", current_time, processes[i].id);
                current_time++;
                processes[i].state = PRONTO;
                
                concluido = 0;
            }
        }
    }
    // Mostra o estado de todos os processos uma última vez
    mostrar_processos(processes,num_processes);
}

// Escalonamento primeiro a chegar, primeiro servido (pcps)
void pcps(Process processes[], int num_processes) {
    int current_time = 0;

    for (int i = 0; i < num_processes; i++) {
        // Mudar o estado do processo para EM_EXECUCAO
        processes[i].state = EM_EXECUCAO;

        // Mostra o estado de todos os processos
        mostrar_processos(processes,num_processes);

        // Executa o processo até a conclusão
        while (processes[i].time_remaining > 0) {
            printf("Tempo %d: executando processo %d (%ds para conclusão)\n", current_time, processes[i].id, processes[i].time_remaining);
            current_time++;
            processes[i].time_remaining--;
        }

        // Mudar o estado do processo para CONCLUIDO
        processes[i].state = CONCLUIDO;
        printf("Tempo %d: processo %d concluído\n", current_time, processes[i].id);
        current_time++;
    }
    printf("Todos os processos foram concluidos.");
}

int main() {
    // Exemplo de utilização
    Process processes[] = {
        {1, 5, PRONTO},
        {2, 3, PRONTO},
        {3, 7, PRONTO}
    };

    int num_processes = sizeof(processes) / sizeof(processes[0]);

    // Primeiro a chegar, primeiro servido
    // pcps(processes, num_processes);

    // Chaveamento circular (round-robin)
    int quantum = 4;
    round_robin(processes, num_processes, quantum);

    return 0;
}