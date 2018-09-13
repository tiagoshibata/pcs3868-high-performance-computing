//PROCESSOS
#include   <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
int *a;
void main()
{
   pid_t pid;
   int status;
   struct shmid_ds *buf;
   int id;
   id=shmget (IPC_PRIVATE, sizeof(int), 0777 | IPC_CREAT); 
   a = shmat (id, 0, 0);
   *a=19;
   pid=fork();
   if ((int)pid == 0) {
      a= shmat (id, 0, 0);
      printf("processo criado a=%d\n",*a);
      fflush(stdout);
      *a=55;
      shmdt (a);
      exit(1);
   }
   waitpid(pid,&status,0);
   printf("main a=%d\n",*a);
   fflush(stdout);
   shmdt (a);
   shmctl (id, IPC_RMID, buf); //remove area compartilhada  
 }

 
        
