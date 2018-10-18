#include <stdio.h>
#include <omp.h>
#include <time.h>
#define n 10
typedef struct {int a; int *proximo;} tipo_lista;
tipo_lista *lista;
tipo_lista *lista_first;
void inicia(int size)
{
  int i;
  tipo_lista *lista_anterior;
  lista=(tipo_lista *) malloc(sizeof(tipo_lista));
  lista->a=0;
  lista_first=lista;
  for (i=1;i<size;i++)
   {
     lista_anterior=lista;
     lista=(tipo_lista *) malloc(sizeof(tipo_lista));
     lista->a=i%5;
     lista_anterior->proximo=lista;
   }
   lista->proximo=(int *) 0;
}


void main()
{
    struct timespec start_time, end_time;
    tipo_lista *prox;
    inicia(n);
    prox=lista_first;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    #pragma omp parallel num_threads(4)
    {
        #pragma omp single
        while (prox) {
            lista=prox;
            #pragma omp task firstprivate(lista)
            {
                printf("%d  thread=%d\n",lista->a, omp_get_thread_num());
                fflush(stdout);
                sleep(lista->a);
            }
            prox=lista->proximo;
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    printf("FIM MAIN\nTime: %.5fms\n",
    (end_time.tv_sec * 1000 + 1e-6 * end_time.tv_nsec) - (start_time.tv_sec * 1000 + 1e-6 * start_time.tv_nsec));
}
