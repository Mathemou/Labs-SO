#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int vet[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

int i = 0;

pthread_mutex_t m;

void * thread(void * arg){
    int sum = 0;
    int lim = *(int*)arg;

    while(1){
        pthread_mutex_lock(&m);
        if(i > lim){
            pthread_mutex_unlock(&m);
            break;
        }
        int i_atual = i;
        i++;
        pthread_mutex_unlock(&m);
        sleep(1);
        sum+=vet[i_atual];
    }

    /* pthread_mutex_lock(&m);
    for(;i<=*(int*)arg;i++){
        int i_atual = i;
        sleep(1);
        sum += vet[i_atual];
    }
    pthread_mutex_unlock(&m); */
    int * res = malloc(sizeof(int));
    *res = sum;
    free(arg);
    pthread_exit(res);
}

int main(){
    pthread_mutex_init(&m, NULL);

    pthread_t p1;
    pthread_t p2;

    int * lim_t1 = malloc(sizeof(int));
    int * lim_t2 = malloc(sizeof(int));
    *lim_t1 = 4;
    *lim_t2 = 9;

    void * res_t1;
    void * res_t2;

    pthread_create(&p1, NULL, thread, lim_t1);
    pthread_create(&p2, NULL, thread, lim_t2);

    pthread_join(p1, &res_t1);
    pthread_join(p2, &res_t2);

    int soma_final = (*(int*)res_t1) + (*(int*)res_t2);
    printf("A soma parcial da primeira thread é: %d\n", (*(int*)res_t1));
    printf("A soma parcial da segunda thread é: %d\n", (*(int*)res_t2));

    printf("A soma final é: %d\n", soma_final);

    free(res_t1);
    free(res_t2);

    pthread_mutex_destroy(&m);


    return 0;
}