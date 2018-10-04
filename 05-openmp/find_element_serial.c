#include <stdio.h>
#include <sys/sysinfo.h>
#include <time.h>

#define SIZE 1000
double A[SIZE][SIZE];

int main() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = (2 * i - j) % 1000;
        }
    }

    for (;;) {
        float target;
        printf("Type target element:\n");
        scanf("%f", &target);

        struct timespec start_time, end_time;
        clock_gettime(CLOCK_MONOTONIC, &start_time);
        double occurences = 0;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                occurences += A[i][j] == target;
            }
        }
        clock_gettime(CLOCK_MONOTONIC, &end_time);
        printf("Occurences: %f, time: %.5fms\n", occurences,
            (end_time.tv_sec * 1000 + 1e-6 * end_time.tv_nsec) - (start_time.tv_sec * 1000 + 1e-6 * start_time.tv_nsec));
    }

    return 0;
}
