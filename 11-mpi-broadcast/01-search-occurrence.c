#include <mpi.h>
#include <stdio.h>


main(argc, argv)

int  argc;
char *argv[];


{
    int n, n_nos, rank, i, valor, vet_ocurrencias[4], indice;
    int vetor[100000], vet_ocorrencias[10000];

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &n_nos);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    n=100000;

    for (i=0; i<n; i++){
        vetor[i] = rand() % 20;
    }

    if  (rank == 0) {
        printf("Valor a ser encontrado (entre 0 e 19): ");
        fflush(stdout);
        scanf("%d", &valor);
    }
    MPI_Bcast(&valor,1,MPI_INT,0,MPI_COMM_WORLD);

    for (i=0; i<n; i++){
        if (vetor[i] == valor) {
            indice = i;
            break;
        }
    }

    MPI_Gather(&indice,1,MPI_INT,vet_ocurrencias,1,MPI_INT,0,MPI_COMM_WORLD);

    if (rank == 0){
        for (i=0; i< n_nos; i++){
            printf("Ocorrência no nó %d com índice %d\n", i, vet_ocurrencias[i]);
            fflush(stdout);
        }
    }
    MPI_Finalize();
    return(0);
}