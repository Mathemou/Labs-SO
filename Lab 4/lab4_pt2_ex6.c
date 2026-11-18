#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int vet_primos[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void * thread(void * arg){
    int idx = *(int*)arg;
    printf("ID: %lu ELEMENTO: %d\n", pthread_self(), vet_primos[idx]);
    free(arg);
    pthread_exit(NULL);
}

int main(){
    pthread_t t1;
    pthread_t t2;
    pthread_t t3;
    pthread_t t4;
    pthread_t t5;
    pthread_t t6;
    pthread_t t7;
    pthread_t t8;
    pthread_t t9;
    pthread_t t10;

    int * um = malloc(sizeof(int));
    *um = 0;
    int * dois = malloc(sizeof(int));
    *dois = 1;
    int * tres = malloc(sizeof(int));
    *tres = 2;
    int * quatro = malloc(sizeof(int));
    *quatro = 3;
    int * cinco = malloc(sizeof(int));
    *cinco = 4;
    int * seis = malloc(sizeof(int));
    *seis = 5;
    int * sete = malloc(sizeof(int));
    *sete = 6;
    int * oito = malloc(sizeof(int));
    *oito = 7;
    int * nove = malloc(sizeof(int));
    *nove = 8;
    int * dez = malloc(sizeof(int));
    *dez = 9;

    pthread_create(&t1, NULL, thread, um);
    pthread_create(&t2, NULL, thread, dois);
    pthread_create(&t3, NULL, thread, tres);
    pthread_create(&t4, NULL, thread, quatro);
    pthread_create(&t5, NULL, thread, cinco);
    pthread_create(&t6, NULL, thread, seis);
    pthread_create(&t7, NULL, thread, sete);
    pthread_create(&t8, NULL, thread, oito);
    pthread_create(&t9, NULL, thread, nove);
    pthread_create(&t10, NULL, thread, dez);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_join(t5, NULL);
    pthread_join(t6, NULL);
    pthread_join(t7, NULL);
    pthread_join(t8, NULL);
    pthread_join(t9, NULL);
    pthread_join(t10, NULL);


    

    return 0;
}