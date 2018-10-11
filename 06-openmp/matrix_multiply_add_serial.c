#include <stdio.h>
#include <sys/sysinfo.h>
#include <time.h>

#define SIZE 1000
int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE], D[SIZE][SIZE];

void matrix_multiply(int result[SIZE][SIZE], int a[SIZE][SIZE], int b[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = 0;
            for (int k = 0; k < SIZE; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

int main() {
    static int A_B[SIZE][SIZE], C_D[SIZE][SIZE], result[SIZE][SIZE];

    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    matrix_multiply(A_B, A, B);
    matrix_multiply(C_D, C, D);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = A_B[i][j] + C_D[i][j];
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);
    printf("[0][0] = %d, [SIZE / 2][SIZE / 2] = %d, [SIZE - 1][SIZE - 1] = %d\nTime: %.5fms\n",
        result[0][0], result[SIZE / 2][SIZE / 2], result[SIZE - 1][SIZE - 1],
        (end_time.tv_sec * 1000 + 1e-6 * end_time.tv_nsec) - (start_time.tv_sec * 1000 + 1e-6 * start_time.tv_nsec));

    return 0;
}
