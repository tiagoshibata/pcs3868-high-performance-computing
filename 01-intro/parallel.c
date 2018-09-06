#include <stdio.h>
#include <sys/sysinfo.h>

#include <omp.h>

int main() {
    int nprocs = get_nprocs();
    printf("nprocs = %d\n", nprocs);
    #pragma omp parallel num_threads(nprocs)
    {
        printf("Hello from thread %d\n", omp_get_thread_num());
    }
    return 0;
}
