
#define _POSIX_SOURCE
#include <stdio.h>  
#include <unistd.h> //pause()
#include <signal.h> //signal()
#include <stdlib.h> //exit()
#include <string.h> //strsignal()
#include <sys/types.h> // pid_t
#include <sys/wait.h> // wait()

// ./cw3c 3 17 ./cw3a ./helper

char *strsignal(int sig);
pid_t getpgid(pid_t pid);
int killpg(pid_t pgid, int sig);

int main(int argc, char *argv[]) {
    if(argc != 5) {
        printf("TOO LITTLE ARGUMENTS\n");
        exit(EXIT_FAILURE);
    }

    int sig = atoi(argv[2]);
    // argv[3] - nazwa prog. z pod. a
    // argv[4] - nazwe prog. pomocnicznego 
    pid_t pid = fork();

    switch (pid)
    {
    case 0: // potomny
        setpgid(pid, 0); 
        int execStatus = execlp(argv[4], argv[4], argv[1], argv[2], argv[3], (char *) NULL);
        if (execStatus == -1) {
            perror("exec error");
            exit(-1);
        };

        break;
    case -1: // error
        perror("fork error");
        exit(-1);
        break;
    default: // macierzysty
        sleep(6);
        int pgid = getpgid(pid);
        if (pgid == -1) {
            perror("process group doesnt exist");
            exit(-1);
        }
        int killStatus = killpg(pgid, sig);
        if (killStatus == -1) {
            perror("kill error");
            exit(-1);  
        }
        int status;
        
        if(wait(&status) == -1) {
            perror("WAIT ERROR\n");
            exit(EXIT_FAILURE);
        }

        if (WIFSIGNALED(status)) {
            printf("Proces zakończony sygnałem nr %d o nazwie '%s'.\n", WTERMSIG(status), strsignal(WTERMSIG(status)));
        } else {
            printf("Proces zakończony z kodem wyjścia %d.\n", WEXITSTATUS(status));
        }

        printf("Pgid zakończonych procesów: %d. \n", pgid);

        break;
    }

    
        exit(EXIT_SUCCESS);
}