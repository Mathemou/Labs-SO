#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int avo_pai[2];
    int pai_filho[2];
    int filho_avo[2];

    if (pipe(avo_pai) == -1) {
        printf("Erro na abertura do pipe avo_pai");
        return 1;
    }

    if (pipe(pai_filho) == -1) {
        printf("Erro na abertura do pipe pai_filho");
        return 1;
    }

    if (pipe(filho_avo) == -1) {
        printf("Erro na abertura do pipe filho_avo");
        return 1;
    }

    int tam_vet;

    printf("[GRANDPARENT] Digite o tamanho do vetor: ");
    scanf("%d", &tam_vet);

    int vet[tam_vet];

    pid_t pai = fork();
    if (pai == -1) {
        printf("Falha ao criar pai");
        return 1;
    }

    if (pai != 0) { // Ou seja, está no avô

        close(avo_pai[0]);
        close(pai_filho[0]);
        close(pai_filho[1]);
        close(filho_avo[1]);

        printf("[GRANDPARENT] Digite os %d elementos: ", tam_vet);
        scanf("%d", &vet[0]);

        for (int i = 1; i < tam_vet; i++) {
            scanf(" %d", &vet[i]);
        }

        write(avo_pai[1], vet, sizeof(vet));
        close(avo_pai[1]);

        read(filho_avo[0], vet, sizeof(vet));
        close(filho_avo[0]);

        printf("[GRANDPARENT] Vetor final: ");
        for (int j = 0; j < tam_vet; j++) {
            printf("%d ", vet[j]);
        }
        printf("\n");
    }

    if (pai == 0) { // Ou seja, é o pai
        pid_t filho = fork();

        if (filho == -1) {
            printf("Erro ao iniciar processo filho.");
            return 1;
        }

        if (filho != 0) {
            close(avo_pai[1]);
            close(pai_filho[0]);
            close(filho_avo[0]);
            close(filho_avo[1]);

            read(avo_pai[0], vet, sizeof(vet));
            close(avo_pai[0]);
            for (int i = 0; i < tam_vet; i++) {
                vet[i] = vet[i] * 3;
            }
            write(pai_filho[1], vet, sizeof(vet));
            close(pai_filho[1]);
            waitpid(filho, NULL, 0);
            exit(0);
        }

        if (filho == 0) {
            close(avo_pai[0]);
            close(avo_pai[1]);
            close(pai_filho[1]);
            close(filho_avo[0]);


            read(pai_filho[0], vet, sizeof(vet));
            close(pai_filho[0]);

            int inicio = 0;
            int fim = tam_vet - 1;
            int aux;
            while (inicio < fim) {
                aux = vet[inicio];
                vet[inicio] = vet[fim];
                vet[fim] = aux;
                inicio++;
                fim--;
            }
            /* printf("[SON] Vetor final: ");
            for (int j = 0; j < tam_vet; j++) {
                printf("%d ", vet[j]);
            } */

            write(filho_avo[1], vet, sizeof(vet));
            close(filho_avo[1]);
            exit(0);
        }
    }

    waitpid(pai, NULL, 0);

    return 0;
}
