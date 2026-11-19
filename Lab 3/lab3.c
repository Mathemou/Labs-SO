#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*Questão 1*/
/* int main (){
    int num;
    printf("Digite um número inteiro: ");
    scanf("%d", &num);
    int pai_filho1[2];
    int filho1_filho2[2];
    int filho2_pai[2];

    if(pipe(pai_filho1)==-1){
        printf("Erro na abertura do pipe pai_filho1");
        return 1;
    }

    if(pipe(filho1_filho2)==-1){
        printf("Erro na abertura do pipe filho1_filho2");
        return 1;
    }

    if(pipe(filho2_pai)==-1){
        printf("Erro na abertura do pipe filho2_pai");
        return 1;
    }

    pid_t f1 = fork();
    if(f1==-1){
        printf("Erro na abertura do processo filho 1");
        return 1;
    }
    if(f1==0){
        read(pai_filho1[0], &num, sizeof(int));
        int num_somado = num + 5;
        write(filho1_filho2[1], &num_somado, sizeof(int));
        close(filho1_filho2[0]);
        close(filho1_filho2[1]);
        close(pai_filho1[0]);
        close(pai_filho1[1]);
        close(filho2_pai[0]);
        close(filho2_pai[1]);
    }

    if(f1!=0){ // Ou seja: É o pai
        pid_t f2 = fork();
        if(f2==-1){
            printf("Erro na abertura do processo filho 2");
            return 1;
        }
        if(f2!=0){ // Garante que continua no pai
            write(pai_filho1[1], &num, sizeof(int));
            close(pai_filho1[0]);
            close(pai_filho1[1]);
            read(filho2_pai[0], &num, sizeof(int));
            close(filho2_pai[0]);
            close(filho2_pai[1]);
            printf("O número que retornou do filho 2: %d\n", num);
            close(filho1_filho2[0]);
            close(filho1_filho2[1]);
        }
        if(f2==0){ // Tá no filho2
            read(filho1_filho2[0], &num, sizeof(int));
            int num_mais_10 = num + 10;
            write(filho2_pai[1], &num_mais_10, sizeof(int));
            close(filho1_filho2[0]);
            close(filho1_filho2[1]);
            close(pai_filho1[0]);
            close(pai_filho1[1]);
            close(filho2_pai[0]);
            close(filho2_pai[1]);
        }

    }
    waitpid(f1, NULL, 0);
    waitpid(f2, NULL, 0);
    return 0;
} */

/*Questão 2*/
/* int main(){
    int ping_grep[2];
    if(pipe(ping_grep)==-1){
        printf("Erro ao inciar o pipe");
        return 1;
    }
    pid_t ping = fork();

    
    if(ping==-1){
        printf("Erro ao iniciar processo ping");
        return 1;
    }
    if(ping==0){ // Tá no processo responsável pelo Ping
        dup2(ping_grep[1], STDOUT_FILENO); // o dup2 já funciona como um write no pipe
        close(ping_grep[0]);
        close(ping_grep[1]);
        execlp("ping", "ping", "-c", "5", "google.com", NULL);
    }
    // Nme preciso de verificar, daqui pra baixo o ping não roda mais
    pid_t grep = fork();
    if(grep==-1){
        printf("Erro ao iniciar processo grep");
        return 1;
    }
    if(grep==0){
        dup2(ping_grep[0], STDIN_FILENO);
        close(ping_grep[0]);
        close(ping_grep[1]);
        execlp("grep", "grep", "rtt", NULL);
    }
    close(ping_grep[0]);
    close(ping_grep[1]);
    waitpid(ping, NULL, 0);
    waitpid(grep, NULL, 0);
    return 0;
}  */

/*Questão 3*/
int main(){
    int tam;
    printf("[GRANDPARENT] Digite o tamanho do vetor: ");
    scanf("%d", &tam);
    int vet[tam];
    printf("[GRANDPARENT] Digite os %d elementos: ", tam);
    scanf(" %d", &vet[0]);
    for(int i=1; i < tam; i++){
        scanf("%d", &vet[i]);
    }

    int avo_filho[2];
    int filho_neto[2];
    int neto_filho[2];
    int filho_avo[2];

    if(pipe(avo_filho)==-1){
        printf("Erro ao iniciar o pipe avo_filho");
        return 1;
    }

    if(pipe(filho_neto)==-1){
        printf("Erro ao iniciar o pipe avo_filho");
        return 1;
    }

    if(pipe(neto_filho)==-1){
        printf("Erro ao iniciar o pipe avo_filho");
        return 1;
    }

    if(pipe(filho_avo)==-1){
        printf("Erro ao iniciar o pipe avo_filho");
        return 1;
    }

    write(avo_filho[1], vet, sizeof(vet));
    close(avo_filho[0]);
    close(avo_filho[1]);

    pid_t filho = fork();
    if(filho==-1){
        printf("Erro ao inciar processo filho");
        return 1;
    }

    if(filho==0){
        read(avo_filho[0], vet, sizeof(vet));

        for(int i = 0; i < tam; i++){ // Multiplica por 3 cada elemnto
            vet[i] = vet[i] * 3;
        }

        write(filho_neto[1], vet, sizeof(vet));

        close(filho_neto[0]);
        close(filho_neto[1]);
        
        read(neto_filho[0], vet, sizeof(vet));

        close(neto_filho[0]);
        close(neto_filho[1]);

        write(filho_avo[1], vet, sizeof(vet));

        close(filho_avo[0]);
        close(filho_avo[1]);

        exit(0);
    }

    pid_t neto = fork();
    if(neto==-1){
        printf("Erro ao iciiar o processo neto");
        return -1;
    }
    if(neto==0){
        read(filho_neto[0], vet, sizeof(vet));
        int inicio = 0;
        int fim = tam - 1;
        int aux;
        while (inicio < fim) {
            aux = vet[inicio];
            vet[inicio] = vet[fim];
            vet[fim] = aux;
            inicio++;
            fim--;
        }
        write(neto_filho[1], vet, sizeof(vet));

        close(filho_neto[0]);
        close(filho_neto[1]);
        close(filho_avo[0]);
        close(filho_avo[1]);
        close(neto_filho[0]);
        close(neto_filho[1]);
        exit(0);
    }


    read(filho_avo[0], vet, sizeof(vet));
    printf("[GRANDPARENT] Vetor final: ");
    for(int i = 0; i < tam; i++){
        printf("%d ", vet[i]);
    }

    close(filho_neto[0]);
    close(filho_neto[1]);
    close(filho_avo[0]);
    close(filho_avo[1]);
    close(neto_filho[0]);
    close(neto_filho[1]);

    waitpid(filho, NULL, 0);
    waitpid(neto, NULL, 0);

    return 0;
}