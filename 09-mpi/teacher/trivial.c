/*
 * Transmit a message in a two process system.
 */
#include <stdio.h>
#include <mpi.h>

#define BUFSIZE		64

int			buf[BUFSIZE];

int
main(argc, argv)

int			argc;
char			*argv[];

{
	int		size, rank;
	MPI_Status	status;
       int i;
/*
 * Initialize MPI.
 */
	MPI_Init(&argc, &argv);
/*
 * Error check the number of processes.
 * Determine my rank in the world group.
 * The sender will be rank 0 and the receiver, rank 1.
 */
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (2 != size) {
		MPI_Finalize();
		return(1);
	}

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
/*
 * As rank 0, send a message to rank 1.
 */
	if (0 == rank) {
            for (i=0;i<64;i++)
              buf[i]=i;	
    	    MPI_Send(buf, BUFSIZE, MPI_INT, 1, 11, MPI_COMM_WORLD);
	}
/*
 * As rank 1, receive a message from rank 0.
 */
	else {
		MPI_Recv(buf, BUFSIZE, MPI_INT, 0, 11, MPI_COMM_WORLD,
				&status);
                for(i=0;i<64;i++)
               {   printf("%d  ",buf[i]);
               fflush(stdout);}
                printf("\n");
	}

	MPI_Finalize();
	return(0);
}
