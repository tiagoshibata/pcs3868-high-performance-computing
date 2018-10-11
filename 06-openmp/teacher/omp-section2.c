// secoes paralelas
//uma das secoes contem uma regiao paralela: a regiao paralela é executada por 2 threads. 

#include <stdio.h>
#include <omp.h>
int i;
int main()
{ printf("INICIO\n");
  omp_set_nested(1);  //permite aninhamento de paralelismo
  omp_set_num_threads(2);
#pragma omp parallel sections
  {
#pragma omp section
  { printf("secao1 %d\n",omp_get_thread_num());
    fflush(stdout);
    for (i=0;i<20000;i++)
     {printf("a");
      fflush(stdout);
     }

    #pragma omp parallel num_threads(2)
     { printf("THREAD %d\n",omp_get_thread_num());
       fflush(stdout);
     } 
   printf("FIM secao1 %d\n",omp_get_thread_num());
    fflush(stdout);
  }
#pragma omp section
  { printf("secao 2 %d\n",omp_get_thread_num());
      for (i=0;i<20000;i++)
     {printf("b");
      fflush(stdout);
     }
   printf("FIM secao2 %d\n",omp_get_thread_num());
    fflush(stdout);
  }
}
  printf("FIM\n");
}

