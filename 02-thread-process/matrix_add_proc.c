#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
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

void initialize(matrices_t *m) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++){
            m->a[i][j] = 1.5;
            m->b[i][j] = 2.6;
        }
    }
}

void child_process(matrices_t *m, int start, int end) {
    for (int row = start; row < end; row++) {
        for (int column = 0; column < SIZE; column++) {
            m->c[row][column] = m->a[row][column] + m->b[row][column];
        }
    }
    exit(0);
}

int main() {
    int nprocs = get_nprocs();
    printf("nprocs = %d\n", nprocs);

    matrices_t *matrices = mmap(NULL, sizeof(matrices_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (matrices == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    initialize(matrices);

    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    pid_t pids[nprocs];
    for (int p = 0; p < nprocs; p++) {
        pids[p] = fork();
        if (!pids[p]) {
            int start = (p * SIZE) / nprocs;
            int end = ((p + 1) * SIZE) / nprocs;
            child_process(matrices, start, end);
        }
    }

    for (int p = 0; p < nprocs; p++) {
        if (waitpid(pids[p], NULL, 0) == -1) {
            perror("waitpid");
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);

    printf("c[0][0] = %f, c[SIZE - 1][SIZE - 1] = %f, c[SIZE / 2][SIZE / 2] = %f\n",
        matrices->c[0][0],
        matrices->c[SIZE - 1][SIZE - 1],
        matrices->c[SIZE / 2][SIZE / 2]);
    printf("Time: %.5fms\n", (end_time.tv_sec * 1000 + 1e-6 * end_time.tv_nsec) - (start_time.tv_sec * 1000 + 1e-6 * start_time.tv_nsec));
}
