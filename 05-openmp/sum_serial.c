#include <stdio.h>
#include <sys/sysinfo.h>
#include <time.h>

#define SIZE 1000
double A[SIZE][SIZE];

int main() {
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = (3 * i - j) / 2;
        }
    }

    double sum = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            sum += A[i][j];
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);
    printf("Sum: %f, time: %.5fms\n", sum,
        (end_time.tv_sec * 1000 + 1e-6 * end_time.tv_nsec) - (start_time.tv_sec * 1000 + 1e-6 * start_time.tv_nsec));

    return 0;
}
