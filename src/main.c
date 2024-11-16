#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "race.h"
#include "progress.h"

int main() {
    srand(time(NULL));  

    pthread_t threads[NUM_THREADS];

    init_threads(threads);

    mostrar_progresso();

    wait_for_threads(threads);

    display_winner();

    return 0;
}
