// Exercicio 1: Programa busca uma sequencia, definida pelo usuario, em um arquivo com varias sequencias 
#include <stdio.h>
#include <stdlib.h>

#define SEQ_SIZE 12
#define TRUE 0
#define FALSE 1

int main()
{
    int i = 0;
    int j;
    int *indice_achou;
    char * buff;
    char sequencia[SEQ_SIZE];
    int file_size;
    char ** seq_vet;
    int n_seq;
    int k;
    FILE *f;
    f = fopen("seq-teste.txt", "r");
    fseek(f,0L,SEEK_END);
    file_size=ftell(f);
    fseek(f,0L,SEEK_SET);
    n_seq=(file_size+1)/(SEQ_SIZE-1);
    seq_vet=(char **)malloc(n_seq*sizeof(char *));
    for (k=0;k<n_seq;k++)
        seq_vet[k]=malloc(SEQ_SIZE*sizeof(char));
    indice_achou=(int *) malloc (n_seq * sizeof(int));
    for (i=0;i<n_seq;i++){
	fgets(seq_vet[i], SEQ_SIZE, f);
        printf("seq_vet[%d] =  %s\n ",i,seq_vet[i]);
   }
        
   printf("file_size=%d\n",file_size);

   printf("Digite a sequencia que deseja buscar: ");
   scanf("%s",&sequencia);
   k=0;
   for (i=0;i<n_seq;i++){	  
        buff=seq_vet[i];
        printf("i=%d buff %s\n ",i,buff);
        for (j = 0; j < SEQ_SIZE-2; j++){
		if (sequencia[j] != buff[j]){
			break;
		}
	}
        if (j== SEQ_SIZE-2) {
              indice_achou[k]=i;
              k++;
        }
   }

   if (k != 0){
	printf("Sequencia encontrada  %d vezes\n",k);
        for (i=0;i<k;i++)
           printf("i=%d  ",indice_achou[i]);
        printf ("\n");
        }
   else
	printf("Sequencia nao encontrada\n ");

   fclose(f);
   return 0;
}
