#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

#define SIZE 10000

double a[SIZE][SIZE];
double b[SIZE][SIZE];
double c[SIZE][SIZE];

void initialize() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++){
            a[i][j] = 1.5;
            b[i][j] = 2.6;
        }
    }
}

int main() {
    initialize();

    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    for (int row = 0; row < SIZE; row++) {
        for (int column = 0; column < SIZE; column++) {
            c[row][column] = a[row][column] + b[row][column];
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);

    printf("c[0][0] = %f, c[SIZE - 1][SIZE - 1] = %f, c[SIZE / 2][SIZE / 2] = %f\n",
        c[0][0],
        c[SIZE - 1][SIZE - 1],
        c[SIZE / 2][SIZE / 2]);
    printf("Time: %.5fms\n", (end_time.tv_sec * 1000 + 1e-6 * end_time.tv_nsec) - (start_time.tv_sec * 1000 + 1e-6 * start_time.tv_nsec));
}
