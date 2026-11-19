#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int vet[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void* thread1(){
    int* sum1 =  malloc(sizeof(int));
    int cum = 0;
    for(int i = 0; i<=4; i++){
        cum += vet[i];
    }
    *sum1 = cum;
    return (void*)sum1;
}

void* thread2(){
    int* sum2 = malloc(sizeof(int));
    int cum = 0;
    for(int i=5;i<10;i++){
        cum += vet[i];
    }
    *sum2 = cum;
    return (void*)sum2;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL,&thread1, NULL);
    pthread_create(&t2, NULL,&thread1, NULL);

    void * retorno_t1;
    void * retorno_t2;
    
    pthread_join(t1, &retorno_t1);
    pthread_join(t2, &retorno_t2);

    int sum = (*(int*)retorno_t1) + (*(int*)retorno_t2);

    printf("%d", sum);
    free(retorno_t1);
    free(retorno_t2);

    return 0;
}