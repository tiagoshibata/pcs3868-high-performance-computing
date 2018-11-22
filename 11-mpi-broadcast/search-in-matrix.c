#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE    1000

int A[SIZE][SIZE];
int job[SIZE];

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

    MPI_Scatter(A, sizeof(A) / sizeof(int), MPI_DOUBLE, job, 1000, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    MPI_Finalize();
    return 0;
}
