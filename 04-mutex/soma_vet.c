#include <stdio.h>
#include <sys/sysinfo.h>
#include <time.h>

#define SIZE 40000000
int a[SIZE];

int main() {
    for (int i = 0; i < SIZE; i++) {
        a[i] = 1.;
    }

    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    int sum = 0;
    for (int i = 0; i < SIZE; i++) {
        sum += a[i];
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    printf("Sum: %d, Time: %.5fms\n", sum, (end_time.tv_sec * 1000 + 1e-6 * end_time.tv_nsec) - (start_time.tv_sec * 1000 + 1e-6 * start_time.tv_nsec));
    return 0;
}
