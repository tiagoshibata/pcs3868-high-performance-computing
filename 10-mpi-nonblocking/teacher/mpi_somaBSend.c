/*
 Soma dos elementos de um vetor, utilizando MPI_BSend.
 Numero de elementos do vetor: multiplo do número de processos.
 */

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

main(argc, argv)

int			argc;
char			*argv[];

{
	int		n,n_nos, rank;
	MPI_Status	status;
        int inicio,fim,vetor[1000],soma_parcial,i;
        int size;
        int soma_total,soma;
        char * buf;
/*
 * Initialize MPI.
 */
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &n_nos);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        n=1000;
        inicio=rank*(n/n_nos);
        fim=inicio+(n/n_nos);
        if (rank==0) {
          for(i=0;i<n;i++)
            vetor[i]=1;
        size=n*4+MPI_BSEND_OVERHEAD*n_nos;
        buf=(char *)malloc(size);  
        MPI_Buffer_attach(buf,size);
          for (i=1;i<n_nos;i++)
          {
             MPI_Bsend(&vetor[0]+n/n_nos,n/n_nos,MPI_INT,i,10,MPI_COMM_WORLD);
          }  
           MPI_Buffer_detach(buf,&size);
        }
        else {
          MPI_Recv(vetor,n/n_nos,MPI_INT,0,10,MPI_COMM_WORLD,&status);
        printf("vetor[0]=%d\n",vetor[0]);
        fflush(stdout);
        }
        soma_parcial=0;
        for(i=0;(i<n/n_nos);i++)
          soma_parcial+=vetor[i];
        printf("soma_parcial=%d\n",soma_parcial);
        fflush(stdout);
        if (rank==0) {
           soma_total=soma_parcial;
           for(i=1;i<n_nos;i++){
             MPI_Recv(&soma,1,MPI_INT,MPI_ANY_SOURCE,11,MPI_COMM_WORLD,&status);
             soma_total+=soma;
           }
           printf("RESULTADO=%d\n",soma_total);
           fflush(stdout);
           }
        else {
           MPI_Send(&soma_parcial,1,MPI_INT,0,11,MPI_COMM_WORLD);
             }
	MPI_Finalize();
	return(0);
}
