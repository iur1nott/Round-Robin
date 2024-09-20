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

char* returnStateStr(int estado) {
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

// Função para escalonar processos usando o algoritmo FCFS
void fcfs(Process processes[], int num_processes) {
    int current_time = 0;

    for (int i = 0; i < num_processes; i++) {
        // Mudar o estado do processo para EM_EXECUCAO
        processes[i].state = EM_EXECUCAO;

        printf("Tempo %d:\n", current_time);

            // Mostra o estado de todos os processos
            for (int j = 0; j < num_processes; j++) {
                printf("\tProcesso %d: %s\n", processes[j].id,returnStateStr(processes[j].state));
            }
        current_time++;
        printf("Tempo %d:\n", current_time);
        printf("\tProcesso %d\n", processes[i].id);
        // Simular a execução do processo até a conclusão
        while (processes[i].time_remaining > 0) {
            processes[i].time_remaining--;
            printf("\t\tTempo restante: %d\n", processes[i].time_remaining);
            current_time++;
        }

        // Mudar o estado do processo para CONCLUIDO
        processes[i].state = CONCLUIDO;

        printf("\t\tProcesso %d concluido\n", processes[i].id);
    }
}

int main() {
    // Exemplo de utilização
    Process processes[] = {
        {1, 5, PRONTO},
        {2, 3, PRONTO},
        {3, 7, PRONTO}
        // Adicione mais processos conforme necessário
    };

    int num_processes = sizeof(processes) / sizeof(processes[0]);

    // Chamar a função de escalonamento FCFS
    fcfs(processes, num_processes);

    // Exibir o estado final dos processos
    printf("Estado final dos processos:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("\tProcesso %d estado: %s\n", processes[i].id, returnStateStr(processes[i].state));
    }

    return 0;
}