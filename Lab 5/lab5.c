
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int primos[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

typedef struct {
    int inicio;
    int fim;
} Parametros;

void *somar_primos(void *arg) {
    Parametros *p = (Parametros *) arg;

    int *soma = malloc(sizeof(int));

    if (soma == NULL) {
        perror("Erro ao alocar memoria");
        return NULL;
    }

    *soma = 0;

    for (int i = p->inicio; i < p->fim; i++) {
        *soma += primos[i];
    }

    return soma;
}

int main() {
    pthread_t threads[2];

    Parametros p1 = {0, 5};
    Parametros p2 = {5, 10};

    int *soma1;
    int *soma2;

    pthread_create(&threads[0], NULL, somar_primos, &p1);
    pthread_create(&threads[1], NULL, somar_primos, &p2);

    pthread_join(threads[0], (void **)&soma1);
    pthread_join(threads[1], (void **)&soma2);

    if (soma1 == NULL || soma2 == NULL) {
        fprintf(stderr, "Erro ao calcular as somas.\n");
        free(soma1);
        free(soma2);
        return 1;
    }

    int soma_total = *soma1 + *soma2;

    printf("Soma parcial da thread 1: %d\n", *soma1);
    printf("Soma parcial da thread 2: %d\n", *soma2);
    printf("Soma total: %d\n", soma_total);

    free(soma1);
    free(soma2);

    return 0;
}
