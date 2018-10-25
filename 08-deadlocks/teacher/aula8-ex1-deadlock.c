#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <omp.h>
sem_t sem1[5];
sem_t sem2[5];
int a[5];
void inicia_a()
{
  int k;
  for (k=0;k<5;k++)
  {
    a[k]=k+1;
  }
}
void calcula(int i)
{ int k;
  for(k=0;k<4;k++)
  { 
    sem_wait(&sem1[i]);
    sem_wait(&sem2[i]);
    printf("ANTES k=%d a[%d]=%d a[%d]=%d \n",k,i,a[i],(i+1)%5,a[(i+1)%5]);
    fflush(stdout);
    a[i]=a[i]+a[(i+1)%5];
    a[(i+1)%5]=a[(i+1)%5]*2-a[i];
    printf("DEPOIS k=%d a[%d]=%d a[%d]=%d \n",k,i,a[i],(i+1)%5,a[(i+1)%5]);
    fflush(stdout);
    sem_post(&sem1[i]);
    sem_post(&sem2[i]);
  }
}
void main()
{ int i;
  printf("INICIO \n");
  fflush(stdout);
  inicia_a();
  for(i=0;i<5;i++) {
    sem_init(&sem1[i],0,5);
    sem_init(&sem2[i],0,5);
  }
  #pragma omp parallel num_threads(5)
  {   
      #pragma omp sections
      {
         #pragma omp section
         calcula(0);
         #pragma omp section
         calcula(1);
         #pragma omp section
         calcula(2);
         #pragma omp section
         calcula(3);
         #pragma omp section
         calcula(4);
      }
  }
      printf("FIM\n");
}      
  
