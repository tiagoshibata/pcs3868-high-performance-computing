// task com regiao paralela
// 2 threads para executar regiao paralela
#include <stdio.h>
#include <omp.h>

int main()
{

     #pragma omp parallel num_threads(2)
     {     
        #pragma omp single
        {
           printf("thread %d\n",omp_get_thread_num());
           printf(" EXEMPLO ");
          #pragma omp task 
           {
            usleep(1);
            printf(" DE thread %d ",omp_get_thread_num());
           }
          #pragma omp task 
           {
            usleep(1);
            printf(" TASK thread %d ",omp_get_thread_num());
           }
        }
     }  // fim da região paralela
     printf("FIM MAIN \n");
     fflush(stdout);
}

