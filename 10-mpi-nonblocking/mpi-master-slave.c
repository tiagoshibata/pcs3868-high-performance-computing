/*
 Master-slave implementation on mpi.
 */

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define WORKTAG 1
#define DIETAG 2
#define NUM_WORKS_REQS 10

static void master();
static void slave();

void (*tab_func[10])();

void func0(){
    int result=0;
    MPI_Send(&result, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
}

void func1(){
    int result=10;
    MPI_Send(&result, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
}

void func2(){
    int result=20;
    MPI_Send(&result, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
}

void func3(){
    int result=30;
    MPI_Send(&result, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
}

void func4(){
    int result=40;
    MPI_Send(&result, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
}

void func5(){
    int result=50;
    MPI_Send(&result, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
}

void func6(){
    int result=60;
    MPI_Send(&result, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
}

void func7(){
    int result=70;
    MPI_Send(&result, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
}

void func8(){
    int result=80;
    MPI_Send(&result, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
}

void func9(){
    int result=90;
    MPI_Send(&result, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
}

void master(){
    int ntasks, rank, work;
    int result;

    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
    work=NUM_WORKS_REQS - 1;

    for (rank=1; rank<ntasks; ++rank){
        MPI_Send(&work, 1, MPI_INT, rank, WORKTAG, MPI_COMM_WORLD);
        work--;
    }

    while (work > -1){
        MPI_Recv(&result, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        printf("Result task from slave %d = %d\n", status.MPI_SOURCE, result);
        fflush(stdout);
        MPI_Send(&work, 1, MPI_INT, status.MPI_SOURCE, WORKTAG, MPI_COMM_WORLD);
        work--;
    }

    for (rank=1;rank<ntasks;++rank){
        MPI_Recv(&result, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        printf("Result task from slave %d = %d\n", status.MPI_SOURCE, result);
        fflush(stdout);
        MPI_Send(0, 0, MPI_INT, status.MPI_SOURCE, DIETAG, MPI_COMM_WORLD);
    }
}

void slave(){
    int work;

    MPI_Status status;
    tab_func[0]=func0;
    tab_func[1]=func1;
    tab_func[2]=func2;
    tab_func[3]=func3;
    tab_func[4]=func4;
    tab_func[5]=func5;
    tab_func[6]=func6;
    tab_func[7]=func7;
    tab_func[8]=func8;
    tab_func[9]=func9;

    for(;;) {
        MPI_Recv(&work, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        if (status.MPI_TAG==DIETAG)
            break;
        (*tab_func[work])();
    }
}

int main(int argc, char *argv[]){
    int myrank;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    if (myrank == 0) {
        master();
    } else {
        slave();
    }

    MPI_Finalize();
    return(0);
}

