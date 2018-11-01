/*
Valor máximo contido em um vetor.
 */
#include <stdio.h>
#include <time.h>

main(argc, argv)

int argc;
char *argv[];

{
    int vetor[100000],i,n;
    int max, max_parcial, max_total;
    struct timespec start_time, end_time;

    clock_gettime(CLOCK_MONOTONIC, &start_time);
    n=100000;

    for(i=0;i<n;i++)
      vetor[i]=rand();

    max_total = 0;

    for(i=0;(i<n);i++) {
      if (vetor[i] > max_total) {
        max_total = vetor[i];
      }
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    printf("RESULTADO=%d \nTime: %.5fms\n",max_total,
    (end_time.tv_sec * 1000 + 1e-6 * end_time.tv_nsec) - (start_time.tv_sec * 1000 + 1e-6 * start_time.tv_nsec));
    fflush(stdout);
	return(0);
}
