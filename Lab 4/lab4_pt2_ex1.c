#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int v[10] = {1, 3, 4, 87, 2, 2, 789, 0, 34, 10};

void *thread1(void *arg) {
    int i = *(int *)arg;
    free(arg);
    unsigned long id = pthread_self();
    printf("ID: %lu Valor no vetor: %d\n", id, v[i]);
    return 0;
}

int main() {
    pthread_t p[10];

    for (int i = 0; i < 10; i++) {
        int * idx = malloc(sizeof(int));
        *idx = i;
        pthread_create(&p[i], NULL, &thread1, idx);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(p[i], NULL);
    }
    return 0;
}