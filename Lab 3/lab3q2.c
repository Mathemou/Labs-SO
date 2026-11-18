#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

// ping -c 5 google.com | grep rtt

int main() {
    int ping_grep[2];

    if (pipe(ping_grep) == -1) {
        printf("Erro no pipe.");
        return 1;
    }

    

    // Vamos criar o primeiro filho, ele vai executar o ping usando o exec,
    // porque se o pai fizer isso o resto do código não é executado
    pid_t ping = fork();

    if (ping == -1) {
        printf("Erro ao inciar filho ping.");
        return 1;
    }

    if (ping == 0) {
        close(ping_grep[0]);
        dup2(ping_grep[1], STDOUT_FILENO);
        close(ping_grep[1]);
        execlp("ping", "ping", "-c", "5", "google.com", NULL);
    }
    
    // Agora podemos criar o segundo filho
    pid_t grep = fork();

    if (grep == -1) {
        printf("Erro ao criar o fork.");
    }

    if (grep == 0) {
        close(ping_grep[1]);
        dup2(ping_grep[0], STDIN_FILENO);
        close(ping_grep[0]);
        execlp("grep", "grep", "rtt", NULL);
    }

    close(ping_grep[0]);
    close(ping_grep[1]);

    waitpid(ping, NULL, 0);
    waitpid(grep, NULL, 0);
    
    return 0;
}