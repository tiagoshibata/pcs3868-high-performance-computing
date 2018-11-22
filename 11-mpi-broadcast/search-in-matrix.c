#include <limits.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE    1000
#define max(a, b)   ((a) > (b) ? (a) : (b))

int A[SIZE][SIZE];

void initialize_data() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = rand();
        }
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int comm_size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (!rank) {
        initialize_data();
    }

    int job_size = SIZE * SIZE / comm_size;
    int job[job_size];
    MPI_Scatter(A, job_size, MPI_INT, job, job_size, MPI_INT, 0, MPI_COMM_WORLD);

    int line_max = INT_MIN;
    for (int i = 0; i < SIZE; i++) {
        line_max = max(line_max, job[i]);
    }

    int global_max;
    MPI_Reduce(&line_max, &global_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if (!rank) {
        printf("Max value: %d\n", global_max);
    }

    MPI_Finalize();
    return 0;
}
