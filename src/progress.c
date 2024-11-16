#include "progress.h"
#include "race.h"
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void mostrar_progresso() {
    while (!corrida_finalizada) {
        usleep(500000);  // Atualiza a cada 0.5 segundos
        pthread_mutex_lock(&progresso_mutex);

        for (int i = 0; i < NUM_THREADS; i++) {
            int passos = dados[i].passos;
            int id = dados[i].id;

            printf("Thread %d: [", id);
            for (int j = 0; j < TAM_BARRA; j++) {
                if (j < (passos * TAM_BARRA) / PASSOS_OBJETIVO) {
                    printf("*");
                } else {
                    printf("-");
                }
            }
            printf("] %d/%d passos\n", passos, PASSOS_OBJETIVO);
        }
        printf("\n");
        pthread_mutex_unlock(&progresso_mutex);
    }
}
