#include "race.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t progresso_mutex = PTHREAD_MUTEX_INITIALIZER;
int corrida_finalizada = 0;
ThreadData dados[NUM_THREADS];

void* correr(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int id = data->id;
    int passos = data->passos;
    int velocidade = data->velocidade;

    printf("Thread %d começa a corrida com velocidade %d!\n", id, velocidade);

    while (passos < PASSOS_OBJETIVO && !corrida_finalizada) {
        usleep(velocidade);

        passos++;
        data->passos = passos;

        if (passos >= PASSOS_OBJETIVO && !corrida_finalizada) {
            pthread_mutex_lock(&progresso_mutex);
            if (!corrida_finalizada) {
                corrida_finalizada = 1;
                printf("Thread %d alcançou o objetivo!\n", id);
            }
            pthread_mutex_unlock(&progresso_mutex);
        }
    }
    return NULL;
}

void init_threads(pthread_t threads[]) {
    for (int i = 0; i < NUM_THREADS; i++) {
        dados[i].id = i + 1;
        dados[i].passos = 0;
        dados[i].velocidade = rand() % 100000 + 50000;
        pthread_create(&threads[i], NULL, correr, (void*)&dados[i]);
    }
}

void wait_for_threads(pthread_t threads[]) {
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
}

void display_winner() {
    printf("\nA corrida terminou!\n");
    for (int i = 0; i < NUM_THREADS; i++) {
        if (dados[i].passos >= PASSOS_OBJETIVO) {
            printf("Thread %d venceu a corrida!\n", dados[i].id);
            break;
        }
    }
}
