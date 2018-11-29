#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE    1000

typedef double matrix_t[SIZE][SIZE];

void initialize(matrix_t m) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            m[i][j] = rand();
        }
    }
}

void node_0_1() {
    static matrix_t a, b;
    initialize(a);
    initialize(b);

    for (int i = 0; i < SIZE; i++) {
        double result[SIZE];
        #pragma omp parallel for num_threads(2)
        for (int j = 0; j < SIZE; j++) {
            result[j] = 0;
            for (int k = 0; k < SIZE; k++) {
                result[j] += a[i][k] * b[k][j];
            }
        }
        MPI_Send(result, SIZE, MPI_DOUBLE, 2, 0, MPI_COMM_WORLD);
    }
}

void node_2() {
    matrix_t result;

    for (int i = 0; i < SIZE; i++) {
        MPI_Recv(result[i], SIZE, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        double y_line[SIZE];
        MPI_Recv(y_line, SIZE, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        #pragma omp parallel for num_threads(2)
        for (int j = 0; j < SIZE; j++) {
            result[i][j] += y_line[j];
        }
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank, comm_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

    switch (rank) {
        case 0:
        case 1:
        node_0_1();
        break;

        case 2:
        node_2();
        break;
    }

    MPI_Finalize();
    return 0;
}
