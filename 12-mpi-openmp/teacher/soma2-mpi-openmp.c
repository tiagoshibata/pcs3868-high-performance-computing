// Exemplo de uso do MPI_Bcast
// Nó 0 inicia vetor, envia todos os seus elementos para os demais nos.
// Todos nos fazem a soma de todos os elementos de vetor

#include <mpi.h>
#include <stdio.h>
#include <omp.h>
#define n 1000
main(argc, argv)

int			argc;
char			*argv[];

{
	int		i,n_nos, rank;
	MPI_Status	status;
        int vetor[n];
        int soma;
        int soma_total;
/*
 * Initialize MPI.
 */
	MPI_Init(&argc, &argv);
/*
 * Error check the number of processes.
 * Determine my rank in the world group.
 * The sender will be rank 0 and the receiver, rank 1.
 */
	MPI_Comm_size(MPI_COMM_WORLD, &n_nos);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        if (rank == 0){
          printf("n_nos=%d\n",n_nos);
          fflush(stdout);
          for(i=0;i<n;i++)
            vetor[i]=1;
        } 
MPI_Scatter(vetor,n/n_nos,MPI_INT,vetor,n/n_nos,MPI_INT,0,MPI_COMM_WORLD);
        omp_set_num_threads(4);
        #pragma omp parallel shared(vetor) private(i) reduction(+:soma)
        {
        soma=0;
        #pragma omp for
          for(i=0;i<n/n_nos;i++)
           {
            soma+=vetor[i];
           }
        }
        MPI_Reduce(&soma,&soma_total,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD); 
        if (rank==0) {
           printf("rank=%d soma=%d\n",rank,soma_total);
           fflush(stdout);
        }
	MPI_Finalize();
	return(0);
}

