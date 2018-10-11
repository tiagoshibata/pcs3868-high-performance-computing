// secoes paralelas
//uma das secoes contem uma regiao paralela: a regiao paralela é executada por 2 threads. 

#include <stdio.h>
#include <omp.h>
int i,j,k;
int main()
{ printf("INICIO\n");
  omp_set_nested(1);  //permite aninhamento de paralelismo
  omp_set_num_threads(2);
#pragma omp parallel sections
{
  #pragma omp section
  { printf("secao1 idthread=%d\n",omp_get_thread_num());
    fflush(stdout);
     for(i=0;i<1000;i++)
       {printf("a");
        fflush(stdout);
       } 
     #pragma omp parallel num_threads(2)
     { printf("regiao paralela 2 idthread %d\n",omp_get_thread_num());
       fflush(stdout);
       for(j=0;j<1000;j++)
         {printf("2");
          fflush(stdout);
         } 
     }
   printf("FIM secao1 idthtread=%d\n",omp_get_thread_num());
    fflush(stdout);
  }
  #pragma omp section
  { 
    printf("secao2= %d\n",omp_get_thread_num());
    fflush(stdout);
     for(k=0;k<2000;k++)
       {printf("b");
        fflush(stdout);
       } 
   printf("FIM secao2 idthtread=%d\n",omp_get_thread_num());
    fflush(stdout);
  }
}
  printf("FIM\n");
}

