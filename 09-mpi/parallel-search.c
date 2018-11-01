#include <fcntl.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static char *mmap_file(int fd, size_t length) {
    void *data = mmap(NULL, length, PROT_READ, MAP_PRIVATE | MAP_POPULATE, fd, 0);
    if (data == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    return data;
}

static inline int same_sequence(char *a, char *b) {
    for (int i = 0; i < 10; i++) {
        if (a[i] != b[i])
            return 0;
    }
    return 1;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int comm_size, rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    char *data;
    struct stat st;
    int message_size;
    if (!rank) {
        if (argc != 2) {
            fprintf(stderr, "Usage: %s data_file\n", *argv);
            return 1;
        }
        int fd = open(argv[1], O_RDONLY, 0);
        if (fd == -1) {
            perror("open");
            return 1;
        }

        fstat(fd, &st);
        data = mmap_file(fd, st.st_size);

        MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
        message_size = st.st_size / comm_size;
        for (int i = 1; i < comm_size; i++) {
            int base = st.st_size * i / comm_size;
            MPI_Send(data + base, message_size, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
    } else {
        MPI_Status status;
        MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_CHAR, &message_size);
        data = malloc(message_size);
        if (!data) {
            perror("malloc");
            return -1;
        }
        MPI_Recv(data, message_size, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    char sequence[11];
    int matches[128];
    int match_count = 0;
    if (!rank) {
        printf("Sequence to look for:\n");
        scanf("%10s", sequence);
    }
    MPI_Bcast(sequence, 10, MPI_CHAR, 0, MPI_COMM_WORLD);
    for (int i = 0; i < message_size; i += 11) {
        char *base = data + i;
        if (same_sequence(base, sequence)) {
            matches[match_count++] = i / 11;
        }
    }

    if (!rank) {
        for (int i = 0; i < match_count; i++) {
            printf("%d\n", matches[i]);
        }
        for (int i = 0; i < comm_size - 1; i++) {
            // Receive data from slaves
            MPI_Status status;
            MPI_Recv(matches, 128, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
            MPI_Get_count(&status, MPI_INT, &match_count);
            for (int i = 0; i < match_count; i++) {
                printf("%d\n", matches[i] + status.MPI_SOURCE * message_size / 11);
            }
        }
        if (munmap(data, st.st_size)) {
            perror("munmap");
            return 1;
        }
    } else {
        MPI_Send(matches, match_count, MPI_INT, 0, 1, MPI_COMM_WORLD);
        free(data);
    }

    MPI_Finalize();
}
