#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

#define SIZE 10000

typedef struct {
    double a[SIZE][SIZE];
    double b[SIZE][SIZE];
    double c[SIZE][SIZE];
} matrices_t;

typedef struct {
    int start;
    int end;
} thread_args_t;

matrices_t matrices;

void initialize(matrices_t *m) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++){
            m->a[i][j] = 1.5;
            m->b[i][j] = 2.6;
        }
    }
}

void *child_thread(void *void_args) {
    thread_args_t *args = (thread_args_t *)void_args;
    for (int row = args->start; row < args->end; row++) {
        for (int column = 0; column < SIZE; column++) {
            matrices.c[row][column] = matrices.a[row][column] + matrices.b[row][column];
        }
    }
}

int main() {
    int nprocs = get_nprocs();
    printf("nprocs = %d\n", nprocs);
    initialize(&matrices);

    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    pthread_t tid[nprocs];
    thread_args_t thread_args[nprocs];
    for (int t = 0; t < nprocs; t++) {
        thread_args[t].start = (t * SIZE) / nprocs;
        thread_args[t].end = ((t + 1) * SIZE) / nprocs;
        if (pthread_create(&tid[t], NULL, child_thread, &thread_args[t])) {
            perror("pthread_create");
            exit(1);
        }
    }

    for (int t = 0; t < nprocs; t++) {
        pthread_join(tid[t], NULL);
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);

    printf("c[0][0] = %f, c[SIZE - 1][SIZE - 1] = %f, c[SIZE / 2][SIZE / 2] = %f\n",
        matrices.c[0][0],
        matrices.c[SIZE - 1][SIZE - 1],
        matrices.c[SIZE / 2][SIZE / 2]);
    printf("Time: %.5fms\n", (end_time.tv_sec * 1000 + 1e-6 * end_time.tv_nsec) - (start_time.tv_sec * 1000 + 1e-6 * start_time.tv_nsec));
}
