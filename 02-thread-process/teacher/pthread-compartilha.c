// o valor de i é passado como um elemento de um vetor : arg_i[i] 
// arg_i:  ponteiro 
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
pthread_t tid;
int a;
void *teste(void *arg)
{
    printf("teste a=%d\n",a);
    fflush(stdout);
    a=55;
}
void main()
{  
   a=19;
   if (pthread_create(&tid,NULL,teste,NULL)) {
       printf("Cannot create thread \n");
       exit(1);
   }   
/* join threads */
   pthread_join(tid,NULL);
   printf("main a=%d\n",a);
   fflush(stdout);
}

