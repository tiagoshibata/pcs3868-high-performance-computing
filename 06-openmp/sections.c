#include <stdio.h>
#include <sys/sysinfo.h>
#include <time.h>

#include <omp.h>

int A[1999], B[2000], C[2000], X[2000], Y[2000];
omp_lock_t a_empty, a_full, b_empty, b_full;

void a_worker() {
    for (int i = 0; i < 1999; i++) {
        omp_set_lock(&a_empty);
        A[i] = 3 * i + 15;
        omp_unset_lock(&a_full);
    }
}

void b_worker() {
    B[0] = 1;
    for (int i = 1; i < 2000; i++) {
        omp_set_lock(&a_full);
        omp_set_lock(&b_empty);
        B[i] = X[i] + A[i - 1];
        omp_unset_lock(&a_empty);
        omp_unset_lock(&b_full);
    }
}

void c_worker() {
    C[0] = 1;
    for (int i = 1; i < 2000; i++) {
        omp_set_lock(&b_full);
        C[i] = Y[i] + B[i - 1] * 2;
        omp_unset_lock(&b_empty);
    }
}

int main() {
    for (int i = 1; i < 2000; i++) {
        X[i] = i;
    }
    for (int i = 1; i < 2000; i++) {
        Y[i] = i + 1;
    }
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    omp_init_lock(&a_empty);
    omp_init_lock(&b_empty);
    omp_init_lock(&a_full);
    omp_init_lock(&b_full);
    omp_set_lock(&a_full);
    omp_set_lock(&b_full);
    #pragma omp parallel sections
    {
        #pragma omp section
        a_worker();
        #pragma omp section
        b_worker();
        #pragma omp section
        c_worker();
    }
    omp_destroy_lock(&a_empty);
    omp_destroy_lock(&b_empty);
    omp_destroy_lock(&a_full);
    omp_destroy_lock(&b_full);

    clock_gettime(CLOCK_MONOTONIC, &end_time);
    printf("C[0] = %d, C[1] = %d, C[1999] = %d\nTime: %.5fms\n",
        C[0], C[1], C[1999],
        (end_time.tv_sec * 1000 + 1e-6 * end_time.tv_nsec) - (start_time.tv_sec * 1000 + 1e-6 * start_time.tv_nsec));

    return 0;
}
