#include <stdio.h>
#include <stdlib.h>

#define SEQ_SIZE 12

int main() {
    int i = 0;
    int j;
    int n_seq;
    int k;
    FILE *f = fopen("seq-teste.txt", "r");
	if (f == NULL) {
        perror("fopen");
	    exit(1);
	}
    fseek(f, 0L, SEEK_END);
    int file_size = ftell(f);
    printf("file_size=%d\n", file_size);
    fseek(f, 0L, SEEK_SET);
    n_seq = (file_size + 1) / (SEQ_SIZE - 1);
    char **seq_vet = (char **)malloc(n_seq * sizeof(char *));
    for (k = 0; k < n_seq; k++)
        seq_vet[k] = malloc(SEQ_SIZE * sizeof(char));
    while (!feof(f)) {
	    fgets(seq_vet[i], SEQ_SIZE, f);
        printf("seq_vet[%d] =  %s\n", i, seq_vet[i]);
        i++;
    }

    printf("Digite a sequencia que deseja buscar: ");
    char sequencia[SEQ_SIZE];
    scanf("%s", &sequencia);
    int igual = 0;
    for (i = 0; i < n_seq; i++){
        char *buff=seq_vet[i];
        printf("i=%d buff %s\n",i,buff);
        for (j = 0; j < SEQ_SIZE-2; j++) {
            if (sequencia[j] != buff[j]) {
                break;
            }
        }
        if (j == SEQ_SIZE-2) {
              igual = 1;
              break;
        }
    }

    if (igual)
        printf("Sequencia encontrada na linha %d\n",i);
    else
        printf("Sequencia nao encontrada i=%d\n",i);
   fclose(f);
   return 0;
}
