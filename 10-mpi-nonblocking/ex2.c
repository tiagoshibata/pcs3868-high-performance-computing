#include <mpi.h>
#include <stdio.h>

#define SIZE    500

void producer_0() {
    int m[SIZE][SIZE];
    int buffer[sizeof *m + MPI_BSEND_OVERHEAD];
    MPI_Buffer_attach(buffer, sizeof(buffer));

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            m[i][j] = i * 2 - j;
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = 1; j < SIZE - 1; j++)
            m[i][j] = m[i + 1][j - 1] * 3 - m[i + 1][j + 1];
        MPI_Bsend(m[i], SIZE, MPI_INT, 3, 0, MPI_COMM_WORLD);
    }
    MPI_Bsend(m[SIZE - 1], SIZE, MPI_INT, 3, 0, MPI_COMM_WORLD);
    int size = sizeof(buffer);
    MPI_Buffer_detach(buffer, &size);
}

void producer_1() {
    int m[SIZE][SIZE];
    int buffer[sizeof *m + MPI_BSEND_OVERHEAD];
    MPI_Buffer_attach(buffer, sizeof(buffer));

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            m[i][j] = i * 3 - j;
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = 1; j < SIZE - 1; j++)
            m[i][j] = m[i + 1][j - 1] * 4 - m[i + 1][j + 1];
        MPI_Bsend(m[i], SIZE, MPI_INT, 3, 0, MPI_COMM_WORLD);
    }
    MPI_Bsend(m[SIZE - 1], SIZE, MPI_INT, 3, 0, MPI_COMM_WORLD);
    int size = sizeof(buffer);
    MPI_Buffer_detach(buffer, &size);
}

void producer_2() {
    int m[SIZE][SIZE];
    int buffer[sizeof *m + MPI_BSEND_OVERHEAD];
    MPI_Buffer_attach(buffer, sizeof(buffer));

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            m[i][j] = i * 2 + j;
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = 1; j < SIZE - 1; j++)
            m[i][j] = m[i + 1][j - 1] * 2 - m[i + 1][j + 1];
        MPI_Bsend(m[i], SIZE, MPI_INT, 3, 0, MPI_COMM_WORLD);
    }
    MPI_Bsend(m[SIZE - 1], SIZE, MPI_INT, 3, 0, MPI_COMM_WORLD);
    int size = sizeof(buffer);
    MPI_Buffer_detach(buffer, &size);
}

void consumer() {
    int result[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        int row[3][SIZE];
        for (int source = 0; source < 3; source++) {
            MPI_Recv(row[source], SIZE, MPI_INT, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        for (int j = 0; j < SIZE; j++)
            result[i][j] = row[0][j] + row[1][j] + row[2][j];
    }
    printf("consumer:\n\tW[0][0] = %d\n\tW[300][400]=%d\n\tW[499][499]=%d\n", result[0][0], result[300][400], result[499][499]);
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int comm_size, rank;

    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    if (comm_size != 4) {
        fprintf(stderr, "Must be run with 4 MPI processes\n");
        return 1;
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    switch (rank) {
        case 0:
        producer_0();
        break;

        case 1:
        producer_1();
        break;

        case 2:
        producer_2();
        break;

        case 3:
        consumer();
        break;
    }

    MPI_Finalize();
    return 0;
}
