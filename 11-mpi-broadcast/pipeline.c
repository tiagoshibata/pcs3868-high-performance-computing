#include <limits.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE    500
#define max(a, b)   ((a) > (b) ? (a) : (b))

double A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE], T[SIZE][SIZE], Z[SIZE][SIZE];

void node_0() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = i + j;
            B[i][j] = 2 * i - j;
        }
    }

    MPI_Request request_Y = NULL;
    for (int i = 0; i < SIZE; i++) {
        double C_line[SIZE];
        MPI_Request request_C;
        MPI_Irecv(C_line, SIZE, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, &request_C);

        double X_line[SIZE];
        for (int j = 0; j < SIZE; j++) {
            X_line[i] = A[i][j] * B[j][i];
        }
        MPI_Request request_X;
        MPI_Isend(X_line, SIZE, MPI_DOUBLE, 2, 0, MPI_COMM_WORLD, &request_X);

        MPI_Wait(&request_C, MPI_STATUS_IGNORE);
        if (request_Y) {
            MPI_Wait(&request_Y, MPI_STATUS_IGNORE);
        }
        double Y_line[SIZE];
        for (int i = 0; i < SIZE; i++) {
            Y_line[i] = X_line[i] * C_line[i];
        }
        MPI_Isend(Y_line, SIZE, MPI_DOUBLE, 2, 1, MPI_COMM_WORLD, &request_Y);

        MPI_Wait(&request_X, MPI_STATUS_IGNORE);
    }
    MPI_Wait(&request_Y, MPI_STATUS_IGNORE);
}

void node_1() {
    MPI_Request request_C = NULL;
    for (int i = 0; i < SIZE; i++) {
        double C_line[SIZE];
        for (int j = 0; j < SIZE; j++) {
            if (request_C) {
                MPI_Wait(&request_C, MPI_STATUS_IGNORE);
            }
            C_line[j] = 2 * i + j;
        }
        MPI_Isend(C_line, SIZE, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &request_C);
    }
    MPI_Wait(&request_C, MPI_STATUS_IGNORE);
}

void node_2() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            T[i][j] = i + j;
        }
    }

    for (int i = 0; i < SIZE; i++) {
        MPI_Request request_X;
        MPI_Request request_Y;
        double X_line[SIZE];
        double Y_line[SIZE];
        MPI_Irecv(X_line, SIZE, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &request_X);
        MPI_Irecv(Y_line, SIZE, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, &request_Y);
        for (int j = 0; j < SIZE; j++) {
            T[i][j] = i + j;
        }
        MPI_Wait(&request_X, MPI_STATUS_IGNORE);
        for (int j = 0; j < SIZE; j++) {
            T[i][j] += X_line[j];
        }
        MPI_Wait(&request_Y, MPI_STATUS_IGNORE);
        for (int j = 0; j < SIZE; j++) {
            T[i][j] += Y_line[j];
        }
    }
    printf("T[0][0] = %f, T[250][250] = %f, T[499][499] = %f\n", T[0][0], T[250][250], T[499][499]);
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
