#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int i;
int n;
int v[1000];

void inicia_vetor(int n) {
    int i;
    for (i = 0; i < n; i++) {
        v[i] = random() % 1000;
    }
}

void merge(int p,int q,int r, int v[]) {
    int i, j, k;
    int v_aux[1000];
    i = p;
    j = q;
    k = 0;
    while (i < q && j < r) {
        if (v[i] <= v[j])
            v_aux[k++] = v[i++];
        else
            v_aux[k++] = v[j++];
    }
    while (i < q)
        v_aux[k++] = v[i++];
    while (j < r)
        v_aux[k++] = v[j++];
    for (i = p; i < r; i++)
        v[i] = v_aux[i - p];
}

void merge_sort(int p,int r,int v[]) {
    int q;
    if (p < r - 1) {
        q = (p + r) / 2;
        #pragma omp task if(r - p >= 32)
        merge_sort(p, q, v);
        #pragma omp task if(r - p >= 32)
        merge_sort(q, r, v);
        merge(p, q, r, v);
    }
}

int main() {
    int i;
    printf("n: ");
    scanf("%d", &n);
    inicia_vetor(n);
    for (i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    #pragma omp parallel num_threads(4)
    {
        #pragma omp single
        merge_sort(0, n, v);
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    printf("Time: %.5fms\n",
        (end_time.tv_sec * 1000 + 1e-6 * end_time.tv_nsec) - (start_time.tv_sec * 1000 + 1e-6 * start_time.tv_nsec));
    for (i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
    return 0;
}
