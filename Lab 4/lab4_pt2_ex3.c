#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int vet[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

void * thread1(){
    int * res = malloc(sizeof(int));
    int sum = 0;
    for(int i=0; i<5;i++){
        sum+=vet[i];
    }
    *res = sum;
    pthread_exit(res);
}

void * thread2(){
    int * res = malloc(sizeof(int));
    int sum = 0;
    for(int i=5; i<10;i++){
        sum+=vet[i];
    }
    *res = sum;
    pthread_exit(res);
}

int main(){
    pthread_t p1;
    pthread_t p2;

    pthread_create(&p1, NULL, thread1, NULL);
    pthread_create(&p2, NULL, thread2, NULL);

    void * r1;
    void * r2;

    pthread_join(p1, &r1);
    pthread_join(p2, &r2);

    printf("A soma é: %d\n", (*(int*)r1)+(*(int*)r2));

    free(r1);
    free(r2);

    return 0;
}