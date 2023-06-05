
#define _POSIX_SOURCE
#include <stdio.h>  
#include <unistd.h> //pause()
#include <signal.h> //signal()
#include <stdlib.h> //exit()
#include <string.h> //strsignal()
#include <sys/types.h> // pid_t
#include <sys/wait.h> // wait()


// ./cw3b 3 17 ./cw3a

char *strsignal(int sig);

int main(int argc, char *argv[]) {
    if(argc != 4) {
        printf("TOO LITTLE ARGUMENTS\n");
        exit(EXIT_FAILURE);
    }

    int sig = atoi(argv[2]);
    pid_t pid = fork();

    switch (pid)
    {
    case 0: ;// potomny
        int execStatus = execlp(argv[3], argv[3], argv[1], argv[2], (char *) NULL);
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

        sleep(7);
        int processStatus = kill(pid, 0);
        if (processStatus == -1) {
            perror("process doesnt exist");
            exit(-1);
        }

        int killStatus = kill(pid, sig);
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

        printf("Pid zakończonego procesu: %d.\n", pid);
        break;
    }
}