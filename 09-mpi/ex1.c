/*
Valor máximo contido em um vetor usando MPI_Send.
Numero de elementos do vetor: multiplo do número de processos.
 */

#include <mpi.h>
#include <stdio.h>
#include <time.h>

main(argc, argv)

int			argc;
char			*argv[];

{
	int n,n_nos, rank;
	MPI_Status status;
    int inicio,fim,vetor[100000],i,k;
    int max, max_parcial, max_total;
    struct timespec start_time, end_time;
/*
 * Initialize MPI.
 */
	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &n_nos);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	clock_gettime(CLOCK_MONOTONIC, &start_time);
    n=100000;
    k=n/n_nos;
    inicio=rank*k;
    fim=inicio+k;
    if (rank==0) {
      for(i=inicio;i<n;i++)
        vetor[i]=rand();
      for (i=1;i<n_nos;i++)
       {
         MPI_Send(&vetor[k*i],k,MPI_INT,i,10,MPI_COMM_WORLD);
         printf("rank=%d APOS SEND\n",rank);
         fflush(stdout);
       }
    }
    else {
      // sleep(5);
      MPI_Recv(vetor,k,MPI_INT,0,10,MPI_COMM_WORLD,&status);
      printf("rank=%d APOS RECV\n",rank);
      fflush(stdout);
    }
    max_parcial=0;
    for(i=0;(i<k);i++) {
      if (vetor[i] > max_parcial) {
        max_parcial = vetor[i];
      }
    }

    printf("rank=%d valor maximo parcial =%d\n",rank,max_parcial);
    fflush(stdout);
    if (rank==0) {
       max_total=max_parcial;
       for(i=1;i<n_nos;i++){
         MPI_Recv(&max,1,MPI_INT,MPI_ANY_SOURCE,11,MPI_COMM_WORLD,&status);
         if (vetor[i] > max) {
           max_total = max;
         }
       }

	   clock_gettime(CLOCK_MONOTONIC, &end_time);
       printf("RESULTADO=%d \nTime: %.5fms\n",max_total,
       (end_time.tv_sec * 1000 + 1e-6 * end_time.tv_nsec) - (start_time.tv_sec * 1000 + 1e-6 * start_time.tv_nsec));
       fflush(stdout);
       }
    else {
    printf("rank=%d max_parcial=%d\n",rank,max_parcial);
    fflush(stdout);
       MPI_Send(&max_parcial,1,MPI_INT,0,11,MPI_COMM_WORLD);
         }
	MPI_Finalize();
	return(0);
}
