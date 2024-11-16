#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "race.h"
#include "progress.h"

int main() {
    srand(time(NULL));  // Inicializa o gerador de números aleatórios

    pthread_t threads[NUM_THREADS];

    // Inicializa os dados das threads
    init_threads(threads);

    // Inicia a função que exibe o progresso da corrida
    mostrar_progresso();

    // Espera todas as threads terminarem
    wait_for_threads(threads);

    // Exibe o vencedor
    display_winner();

    return 0;
}
