#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define SEQ_SIZE 12

static inline int is_same_sequence(char *a, char *b) {
    for (int j = 0; j < SEQ_SIZE - 2; j++) {
        if (a[j] != b[j]) {
            return 0;
        }
    }
    return 1;
}

int search(char **v, int size, char *s) {
    int search_base = 0;
    _Atomic int found = 0;
    #pragma omp parallel
    {
        int i, stop;
        #pragma omp critical
        {
            i = search_base;
            search_base += size / omp_get_num_threads();
        }
        stop = search_base < size ? search_base : size;
        printf("Thread %d: %d -> %d\n", omp_get_thread_num(), i, stop);

        while (i < stop && !found) {
            if (is_same_sequence(s, v[i])) {
                found = i;
                break;
            }
            i++;
        }
    }
    return found;
}

int main() {
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
    int n_seq = (file_size + 1) / (SEQ_SIZE - 1);
    char **seq_vet = (char **)malloc(n_seq * sizeof(char *));
    for (k = 0; k < n_seq; k++)
        seq_vet[k] = malloc(SEQ_SIZE * sizeof(char));
    int i = 0;
    while (!feof(f)) {
	    fgets(seq_vet[i], SEQ_SIZE, f);
        printf("seq_vet[%d] =  %s\n", i, seq_vet[i]);
        i++;
    }

    printf("Digite a sequencia que deseja buscar: ");
    char sequencia[SEQ_SIZE];
    scanf("%s", sequencia);

    int match = search(seq_vet, n_seq, sequencia);
    if (match)
        printf("Sequencia encontrada na linha %d\n", match);
    else
        printf("Sequencia nao encontrada\n");
   fclose(f);
   return 0;
}
