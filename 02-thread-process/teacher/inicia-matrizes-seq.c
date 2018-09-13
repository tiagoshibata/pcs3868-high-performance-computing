#include <stdio.h>
#define size 1000
#define n_threads 3
#include <pthread.h>
#include <stdlib.h>
double a[1000][1000], b[1000][1000];
int n_iter;
pthread_t tid[n_threads];
void *inicia_matrizes(void *arg)
{  int i,j,inicio,fim,k;
   k=*(int *)arg;   
   inicio=(k+1)*n_iter;
   fim=inicio+n_iter;
   printf("inicio=%d  fim=%d   k=%d   n_iter=%d\n",inicio,fim,k,n_iter);
   for (i=inicio;i<fim;i++)
       for (j=0;j<size;j++){
               a[i][j]=1.5;
               b[i][j]=2.6;
   }
}
void main()
{  int i,k,id_thread[n_threads];
   int p=-1;
   int inicio,fim;
   n_iter=size/(n_threads+1);
   //inicia as matrizes   -  3 threads e principal
   for (k=0;k<n_threads;k++) {
       id_thread[k]=k;
       if (pthread_create(&tid[k],NULL,inicia_matrizes,(void *)&id_thread[k])) {
          printf("Cannot create thread %d\n",i);
          exit(1);
       }
   }
   inicia_matrizes((void *)&p);
/* join threads */
  for (i=0;i<n_threads;i++) {
        pthread_join(tid[i],NULL);
  }
  printf("a[0][0]=%f   a[15][20]=%f  b[15][20]=%f  b[size-1][size-1]=%f \n",a[0][0],a[15][20],b[15][20],b[size-1][size-1]);
}
   

        

        
   

