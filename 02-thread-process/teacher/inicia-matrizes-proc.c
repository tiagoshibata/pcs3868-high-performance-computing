#include <stdio.h>
#define size 1000
#define n_processos 3
#include   <sys/shm.h>
#include <stdlib.h>
typedef struct {
   double a[1000][1000], b[1000][1000];
} matrizes;
matrizes *matriz;
pid_t pid_p;
void main()
{  int i,j,k;
   pid_t pid[n_processos];
   int status;
   struct shmid_ds *buf;
   int id;
   int n_iter,inicio,fim;
   id=shmget (IPC_PRIVATE, sizeof(matrizes), 0777 | IPC_CREAT);
   matriz= shmat (id, 0, 0);
   //inicializa as matrizes   -  3 processos
   n_iter=size/(n_processos+1);
   inicio=0;
   fim=n_iter;
   k=-1;
   do {
     k++; 
     pid_p=fork();
     if ((int)pid_p != 0)   //pai
       pid[k]=pid_p;
   }while((pid_p !=0) & (k<(n_processos-1)));
   if ((int)pid_p == 0){     //filhos
        matriz= shmat (id, 0, 0);
        inicio=(k+1)*n_iter;
        fim=inicio+n_iter;
   }
   printf("inicio=%d  fim=%d   k=%d   n_iter=%d\n",inicio,fim,k,n_iter);
   for (i=inicio;i<fim;i++)
       for (j=0;j<size;j++){
               ((matrizes *)matriz)->a[i][j]=1.5;
               ((matrizes *)matriz)->b[i][j]=2.6;
      }
   if ((int)pid_p == 0){     //filhos
      shmdt (matriz);
      exit(1);
   }
   // fim da inicializacao
   for (k=0;k<n_processos;k++) 
      waitpid(pid[k],&status,0);
   printf("a[0][0]=%f   a[15][20]=%f  b[15][20]=%f  b[size-1][size-1]=%f \n",((matrizes *)matriz)->a[0][0],((matrizes *)matriz)->a[15][20],((matrizes *)matriz)->b[15][20],((matrizes *)matriz)->b[size-1][size-1]);
      shmdt (matriz);
      shmctl (id, IPC_RMID, buf); //remove area compartilhada
}

        

        
   

