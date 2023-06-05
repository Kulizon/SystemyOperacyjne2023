#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <ctype.h>

char *strsignal(int sig);

void customSignalHandler(int sig) {
    printf("\nSygnał nr. %d o nazwie '%s' został przechywycony! \n", sig,  strsignal(sig));
}

int main(int argc, char *argv[]) {
    if(argc != 3)  {
        printf("TOO LITTLE ARGUMENTS\n");
        exit(EXIT_FAILURE);
    }

    char option = atoi(argv[1]);
    int sig = atoi(argv[2]);

    printf("PID tego procesu to: %d\n", getpid());

    switch (option)
    {
    case 1: // wykonywanie domyślnej funkcjonalności
        if (signal(sig, SIG_DFL) == SIG_ERR) {
            perror ("ERROR IN DEFAULT CASE");
            exit(EXIT_FAILURE);
        }
        break;
    case 2: // ignorowanie sygnału
        if (signal(sig, SIG_IGN) == SIG_ERR) {
            perror ("ERROR IN IGNORE CASE");
            exit(EXIT_FAILURE);
        }
        break;
    case 3: // własna obsługa sygnału
        if (signal(sig, customSignalHandler) == SIG_ERR) {
            perror ("ERROR IN CUSTOM CASE");
            exit(EXIT_FAILURE);
        }
        break;
    default:
        perror("WRONG ARGUMENTS\n");
        exit(EXIT_FAILURE);
        break;
    }

    pause();
    exit(EXIT_SUCCESS);
}