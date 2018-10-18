#include <stdio.h>
#include <omp.h>
int i;
int n;
int fib(int n)
{
  int i, j;
  if (n<2)
    return n;
  else
  {
    #pragma omp task shared(i) firstprivate(n)
    {
      printf("n=%d thread=%d\n",n,omp_get_thread_num());
      fflush(stdout);
      i=fib(n-1);
      printf("n=%d APOS thread=%d\n",n,omp_get_thread_num());
      fflush(stdout);
    }
    #pragma omp task shared(j) firstprivate(n)
    {
      printf("n-2=%d thread=%d\n",n,omp_get_thread_num());
      fflush(stdout);
      j=fib(n-2);
      printf("n-2=%d APOS thread=%d\n",n,omp_get_thread_num());
      fflush(stdout);
    }

    #pragma omp taskwait
    return i+j;
  }
}
void main()
{printf("n:");
 scanf("%d",&n);
 printf("n=%d",n); 
 printf("thread=%d\n",omp_get_thread_num());
 fflush(stdout);
 printf("fib(%d)=%d\n",n,fib(n));
}

