#ifndef RACE_H
#define RACE_H

#include <pthread.h>  // Adicionar para reconhecer pthread_t e pthread_mutex_t

#define NUM_THREADS 5
#define PASSOS_OBJETIVO 100

// Estrutura para passar parâmetros para as threads
typedef struct {
    int id;
    int passos;
    int velocidade;  // Velocidade (tempo de espera entre passos) para cada thread
} ThreadData;

extern pthread_mutex_t progresso_mutex;  // Mutex para controle de progresso
extern int corrida_finalizada;           // Indica se a corrida terminou
extern ThreadData dados[NUM_THREADS];    // Dados das threads

void* correr(void* arg);
void init_threads(pthread_t threads[]);
void wait_for_threads(pthread_t threads[]);
void display_winner();

#endif