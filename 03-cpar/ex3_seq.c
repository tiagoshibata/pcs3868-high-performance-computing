#include <stdio.h>
#include <time.h>

int a[1000][1000];
int valor_busca;

void init_vetor()
{
  int i,j;
  for(i=0; i<1000; i++)
  {
    for(j=0; j<1000; j++)
    {
      a[i][j] = i + j;
    }
  }
}

void busca_vetor()
{
 int i,j; 
  for(i=0; i<1000; i++)
  {
    for(j=0; j<1000; j++)
    {
      if(a[i][j] == valor_busca)
      {
        printf("encontrado posicao %d %d\n", i, j);
        fflush(stdout);
      }
    }
  }
}

int main(){
  struct timespec start_time, end_time;

  printf("Busca um elemento no vetor.\n");
  clock_gettime(CLOCK_MONOTONIC, &start_time);
  init_vetor();
  clock_gettime(CLOCK_MONOTONIC, &end_time);
  printf("Vetor inicializado, Time: %.5fms\n", (end_time.tv_sec * 1000 + 1e-6 * end_time.tv_nsec) - (start_time.tv_sec * 1000 + 1e-6 * start_time.tv_nsec));
  printf("Informe um elemento: ");
  scanf("%d", &valor_busca);
  clock_gettime(CLOCK_MONOTONIC, &start_time);
  busca_vetor();
  clock_gettime(CLOCK_MONOTONIC, &end_time);
  printf("Busca finalizada, Time: %.5fms\n", (end_time.tv_sec * 1000 + 1e-6 * end_time.tv_nsec) - (start_time.tv_sec * 1000 + 1e-6 * start_time.tv_nsec));
}
