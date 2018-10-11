#include <stdio.h>
#include <omp.h>

int main()
{
//omp_set_dynamic(0);
omp_set_num_threads(6);
#pragma omp parallel 
  {
     printf("TESTE %d\n",omp_get_thread_num());
     fflush(stdout);
     #pragma omp single
       {
           printf("SINGLE %d\n",omp_get_thread_num());
           fflush(stdout);
       }
      printf("XXXX\n");
      fflush(stdout);
  }
}

