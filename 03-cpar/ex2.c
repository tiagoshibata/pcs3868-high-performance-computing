#include <stdio.h>
#include <time.h>

double a[100][100], b[100][100], c[100][100], d[100][100];
double a_b[100][100], c_d[100][100], result[100][100];

double time_difference(struct timespec *start, struct timespec *end) {
    return (end->tv_sec * 1000 + 1e-6 * end->tv_nsec) -
        (start->tv_sec * 1000 + 1e-6 * start->tv_nsec);
}

int main() {
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            a[i][j] = i + j;
        }
    }
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            b[i][j] = i + 2 * j;
        }
    }
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            c[i][j] = 2 * i + 3 * j;
        }
    }
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            d[i][j] = 2 * i + j;
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    printf("Initialization time: %.5fms\n", time_difference(&start_time, &end_time));

    clock_gettime(CLOCK_MONOTONIC, &start_time);
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            a_b[i][j] = 0;
            for (int k = 0; k < 100; k++) {
                a_b[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            c_d[i][j] = 0;
            for (int k = 0; k < 100; k++) {
                c_d[i][j] += c[i][k] * d[k][j];
            }
        }
    }
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            result[i][j] = a_b[i][j] + c_d[i][j];
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    printf("Processing time: %.5fms\n", time_difference(&start_time, &end_time));
    printf("[0][0] = %f, [50][50] = %f, [99][99] = %f\n", result[0][0], result[50][50], result[99][99]);
 }
