#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

/*Questão 7 - Primeira parte*/
/* int vet[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void * thread_0_4(){
    int * sum_total = malloc(sizeof(int));
    int soma_parcial = 0;
    for(int i=0;i<=4;i++){
        soma_parcial += vet[i];
    }
    *sum_total = soma_parcial;
    return (void*) sum_total;
}

void * thread_5_9(){
    int * sum_total = malloc(sizeof(int));
    int soma_parcial = 0;
    for(int i=5;i<=9;i++){
        soma_parcial += vet[i];
    }
    *sum_total = soma_parcial;
    return (void*) sum_total;
}

int main(){
    pthread_t primeira_thread;
    pthread_t segunda_thread;

    pthread_create(&primeira_thread, NULL, &thread_0_4, NULL);
    pthread_create(&segunda_thread, NULL, &thread_5_9, NULL);

    void * retorno1;
    void * retorno2;

    pthread_join(primeira_thread, &retorno1);
    pthread_join(segunda_thread, &retorno2);

    int resultado_final = (*(int*)retorno1 + *(int*)retorno2);

    printf("%d", resultado_final);

    free(retorno1);
    free(retorno2);

    return 0;
} */

/*Questão 1 - Parte 2*/
/* int vet[10] = {56, 78, 34, 56, 78, 34, 56, 78, 34, 89};


void * thread_func(void * arg){
    int pos = *(int*)arg;
    printf("ID [%ld] : %d\n", pthread_self(), vet[pos]);
    free(arg);
    return 0;
}


int main(){
    pthread_t thread[10];
    for(int i=0; i < 10; i++){
        int * idx = malloc(sizeof(int));
        *idx = i;
        pthread_create(&thread[i], NULL, &thread_func, idx);
    }
    for(int i=0;i<10;i++){
        pthread_join(thread[i], NULL);
    }
    return 0;
} */

/*Questão 2 - Parte 2*/
/* int vet[10] = {56, 78, 34, 56, 78, 34, 56, 78, 34, 89};


void * thread_func(void * arg){
    int pos = *(int*)arg;
    printf("ID [%ld] : %d\n", pthread_self(), vet[pos]);
    free(arg);
    return 0;
}


int main(){
    pthread_t thread[10];
    for(int i=0; i < 10; i++){
        int * idx = malloc(sizeof(int));
        *idx = i;
        pthread_create(&thread[i], NULL, &thread_func, idx);
        pthread_join(thread[i], NULL);
    }
    return 0;
} */


/*Questão 3 - Parte 2*/
/* int vet[10] = {5, 6, 45, 1, 8, 3, 9, 12, 7, 76};

void * thread1(){
    int sum_parcial = 0;
    for(int i=0;i<5;i++){
        sum_parcial += vet[i];
    }
    int * soma = malloc(sizeof(int));
    *soma = sum_parcial;
    return soma;
}

void * thread2(){
    int sum_parcial = 0;
    for(int i=5;i<10;i++){
        sum_parcial += vet[i];
    }
    int * soma = malloc(sizeof(int));
    *soma = sum_parcial;
    return soma;
}

int main(){
    pthread_t t1, t2;

    pthread_create(&t1, NULL, &thread1, NULL);
    pthread_create(&t2, NULL, &thread2, NULL);

    void * parte1;
    void * parte2;

    pthread_join(t1, &parte1);
    pthread_join(t2, &parte2);

    printf("Soma: %d\n", (*(int*)parte1 + *(int*)parte2));

    free(parte1);
    free(parte2);

    return 0;
} */

/*Questão 4 - Parte 2*/
/* int global = 0;

int vet[10] = {67, 6, 7, 670, 87, 77, 777, 17, 57, 90};

void * thread1(){
    for(int i = 0; i < 5; i++){
        global += vet[i];
    }
    return 0;
}

void * thread2(){
    for(int i = 5; i < 10; i++){
        global += vet[i];
    }
    return 0;
}

int main(){
    pthread_t p1, p2;

    pthread_create(&p1, NULL, &thread1, NULL);
    pthread_create(&p2, NULL, &thread2, NULL);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    printf("%d\n", global);

    return 0;


} */

/*Questão 5 - Parte 2*/
/* int global = 0;

int vet[10] = {67, 6, 7, 670, 87, 77, 777, 17, 57, 90};

pthread_mutex_t m;

void * thread1(){
    for(int i = 0; i < 5; i++){
        pthread_mutex_lock(&m);
        global += vet[i];
        pthread_mutex_unlock(&m);
    }
    return 0;
}

void * thread2(){
    for(int i = 5; i < 10; i++){
        pthread_mutex_lock(&m);
        global += vet[i];
        pthread_mutex_unlock(&m);
    }
    return 0;
}

int main(){
    pthread_mutex_init(&m, NULL);

    pthread_t p1, p2;

    pthread_create(&p1, NULL, &thread1, NULL);
    pthread_create(&p2, NULL, &thread2, NULL);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    printf("%d\n", global);

    pthread_mutex_destroy(&m);

    return 0;
} */

/*Questão 6 - Parte 2*/
int vet[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void* thread(void*arg){
    int id = *(int*)arg;
    printf("ID: %ld\t Número %d na posição %d\n", pthread_self(), vet[id], id);
    free(arg);
    return 0;
}

int main(){
    pthread_t t[10];
    for(int i =0; i < 10; i++){
        int * idx = malloc(sizeof(int));
        *idx = i;
        pthread_create(&t[i], NULL, &thread, idx);
    }
    for(int i = 0; i < 10; i++){
        pthread_join(t[i], NULL);
    }
}