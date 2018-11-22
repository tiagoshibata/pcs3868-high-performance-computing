#include <limits.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE    500
#define max(a, b)   ((a) > (b) ? (a) : (b))

int B[SIZE][SIZE], Z[SIZE][SIZE];

void node_0() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            B[i][j] = 2 * i - j;
        }
    }

    MPI_Request request_Y = NULL;
    for (int i = 0; i < SIZE; i++) {
        int A_line[SIZE];
        for (int j = 0; j < SIZE; j++) {
            A_line[j] = i + j;
        }
        int C_line[SIZE];
        MPI_Request request_C;
        MPI_Irecv(C_line, SIZE, MPI_INT, 1, 0, MPI_COMM_WORLD, &request_C);

        int X_line[SIZE];
        for (int j = 0; j < SIZE; j++) {
            X_line[j] = 0;
            for (int k = 0; k < SIZE; k++) {
                X_line[j] += A_line[k] * B[k][j];
            }
        }
        MPI_Request request_X;
        MPI_Isend(X_line, SIZE, MPI_INT, 2, 0, MPI_COMM_WORLD, &request_X);

        MPI_Wait(&request_C, MPI_STATUS_IGNORE);
        if (request_Y) {
            MPI_Wait(&request_Y, MPI_STATUS_IGNORE);
        }
        int Y_line[SIZE];
        for (int i = 0; i < SIZE; i++) {
            Y_line[i] = X_line[i] + C_line[i];
        }
        MPI_Isend(Y_line, SIZE, MPI_INT, 2, 1, MPI_COMM_WORLD, &request_Y);

        MPI_Wait(&request_X, MPI_STATUS_IGNORE);
    }
    MPI_Wait(&request_Y, MPI_STATUS_IGNORE);
}

void node_1() {
    MPI_Request request_C = NULL;
    for (int i = 0; i < SIZE; i++) {
        int C_line[SIZE];
        for (int j = 0; j < SIZE; j++) {
            if (request_C) {
                MPI_Wait(&request_C, MPI_STATUS_IGNORE);
            }
            C_line[j] = 2 * i + j;
        }
        MPI_Isend(C_line, SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD, &request_C);
    }
    MPI_Wait(&request_C, MPI_STATUS_IGNORE);
}

void node_2() {
    for (int i = 0; i < SIZE; i++) {
        MPI_Request request_X;
        MPI_Request request_Y;
        int X_line[SIZE];
        int Y_line[SIZE];
        MPI_Irecv(X_line, SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD, &request_X);
        MPI_Irecv(Y_line, SIZE, MPI_INT, 0, 1, MPI_COMM_WORLD, &request_Y);
        for (int j = 0; j < SIZE; j++) {
            Z[i][j] = i + j;
        }
        MPI_Wait(&request_X, MPI_STATUS_IGNORE);
        for (int j = 0; j < SIZE; j++) {
            Z[i][j] += X_line[j];
        }
        MPI_Wait(&request_Y, MPI_STATUS_IGNORE);
        for (int j = 0; j < SIZE; j++) {
            Z[i][j] += Y_line[j];
        }
    }
    printf("Z[0][0] = %d, Z[200][100] = %d, Z[499][499] = %d\n", Z[0][0], Z[200][100], Z[499][499]);
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    switch (rank) {
        case 0:
        node_0();
        break;

        case 1:
        node_1();
        break;

        case 2:
        node_2();
        break;
    }

    MPI_Finalize();
    return 0;
}
