#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int vet[1000];

struct InicioFim {
    int inicio;
    int fim;
};

void *thread(void *arg) {
    int *sum = malloc(sizeof(int));
    *sum = 0;
    struct InicioFim inicio_fim = *(struct InicioFim*)arg;
    int inicio = inicio_fim.inicio;
    int fim  = inicio_fim.fim;
    for(int i = inicio; i <= fim; i++){
        *sum += vet[i];
    }
    
    pthread_exit(sum);
}

int main() {
    // Populando o vetor
    for (int i = 0; i < 1000; i++) {
        vet[i] = i + 1;
    }
    printf("Digite o número de threads à seres utilizadas: ");
    int num_threads;
    scanf("%d", &num_threads);
    pthread_t threads[num_threads];
    struct InicioFim i_f_vet[num_threads];
    int intervalo = 1000 / num_threads;
    int total_sum = 0;

    for (int i = 0; i < num_threads; i++) {
        i_f_vet[i].inicio = i * intervalo;
        i_f_vet[i].fim = ((i + 1) * intervalo) - 1;
        if (i == num_threads - 1) { // última struct
            i_f_vet[i].fim += (1000 % num_threads);
        }
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, thread, (void*)&i_f_vet[i]);
    }

    for(int i =0; i < num_threads; i++){
        void * partial_sum;
        pthread_join(threads[i], &partial_sum);
        total_sum += *(int*)partial_sum;
        free(partial_sum);
    }

    printf("Soma total: %d\n", total_sum);

    /* for (int i = 0; i < num_threads; i++) {
        printf("[%d] Início: %d\t Fim: %d\n", i, i_f_vet[i].inicio,
               i_f_vet[i].fim);
    } */

    /* for (int i=0; i<1000; i++){
        printf("%d ", vet[i]);
    } */
    return 0;
}