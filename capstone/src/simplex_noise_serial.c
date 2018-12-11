#include <stdio.h>
#include <time.h>

#include "simplex_noise.h"

int main() {
    // for (float x = 0; x < 10; x += 0.05) {
    //     printf("%f\n", simplex_noise_1d(x));
    // }
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for (int x = 0; x < 400; x++) {
        printf("%f %f\n", 0.05*x, simplex_noise_fractal_1d(12, 0.05*x));
        fflush(stdout);
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);
    printf("time: %.5fms\n", (end_time.tv_sec * 1000 + 1e-6 * end_time.tv_nsec) - (start_time.tv_sec * 1000 + 1e-6 * start_time.tv_nsec));
    return 0;
}
