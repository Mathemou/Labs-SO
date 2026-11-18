#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    // Primeiro vamos criar os pipes.
    int pai_filho1[2]; // Vai levar o inteiro do pai para o filho
    int filho1_filho2[2]; // Vai levar do filho 1 pro 2
    int filho2_pai[2]; // Vai levar do filho 2 direto pro pai

    // Vamos fazer uma verificação de segurança enquanto já criamos o pipe.
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

    // 1. O processo lê um número inteiro da entrada padrão.
    int n;
    printf("Digite um número inteiro: ");
    scanf("%d", &n);

    // Vamos criar o primeiro filho
    pid_t f1 = fork();
    if(f1==-1){
        printf("Erro na criação do primeiro filho.");
        return 1;
    }

    // Vamos criar o segundo filho, vai criar nos dois, mas eu já mato o neto depois
    
    pid_t f2 = fork();
    if(f2==-1){
        printf("Erro na criação do segundo filho.");
        return 1;
    }
    
    // Se f2 for filho do filho1, já mata logo
    if(f1==0&&f2==0){
        exit(0);
    }
    

    // Vamos setar as configurações do pipe para o pai
    if(f1!=0&&f2!=0){// Ou seja, é o pai
        close(pai_filho1[0]); // 0 é ler, o pai não vai ler da pipe, apenas escrever
        close(filho1_filho2[0]); // Nem lê
        close(filho1_filho2[1]); // Nem escreve nesse pipe
        close(filho2_pai[1]); // Não escreve nada nesse, só lê
    }
    // Agora do pipe do primeiro filho
    if(f1==0){
        close(pai_filho1[1]); // 1 é escrita, o filho não vai escrever, apenas ler
        close(filho1_filho2[0]); // Não vai ler nada do filho 2, só escrever
        close(filho2_pai[0]); // Nem lê
        close(filho2_pai[1]); // Nem escreve nesse pipe
    }

    if(f2==0){
        close(pai_filho1[0]);
        close(pai_filho1[1]);
        close(filho1_filho2[1]);
        close(filho2_pai[0]);
    }

    // 2. O número é enviado para o processo filho através de um pipe.
    if(f1!=0&&f2!=0){ // pai
        write(pai_filho1[1], &n, sizeof(int));
        close(pai_filho1[1]);
    }

    if(f1==0){ // filho 1
        read(pai_filho1[0], &n, sizeof(int));
        close(pai_filho1[0]);
        n+=5;
        write(filho1_filho2[1], &n, sizeof(int));
        close(filho1_filho2[1]);
        waitpid(f2, NULL, 0);
        exit(0);
    }

    if(f2==0){
        read(filho1_filho2[0], &n, sizeof(int));
        close(filho1_filho2[0]);
        n+=10;
        write(filho2_pai[1], &n, sizeof(int));
        close(filho2_pai[1]);
        exit(0);
    }

    if(f1!=0&&f2!=0){
        read(filho2_pai[0], &n, sizeof(int));
        close(filho2_pai[0]);
        waitpid(f1, NULL, 0);
        waitpid(f2, NULL, 0);
        printf("[PARENT] Resultado Final: %d\n", n);
    }


    return 0;
}