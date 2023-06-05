#include <stdio.h>  
#include <unistd.h> //pause()
#include <signal.h> //signal()
#include <stdlib.h> //exit()
#include <string.h> //strsignal()
#include <sys/types.h> // pid_t
#include <sys/wait.h> // wait()

char *strsignal(int sig);

void customSignalHandler(int sig) {
    printf("\nSygnał nr. %d o nazwie '%s' został przechywycony! \n", sig, strsignal(sig));
}

int main(int argc, char *argv[]) {
    // argv[1] - tryb
    // argv[2] - process id
    // argv[3] - nazwa programu z a

    printf("args: %s\n", argv[3]);
    for(int i = 0; i < 5; i++) {
        int pid = fork();

        switch (pid)
        {
        case 0: ;// potomny
            int execStatus = execlp(argv[3], argv[3], argv[1], argv[2], (char *) NULL);
            if (execStatus == -1) {
                perror("exec error");
                exit(-1);
            }
            break;
        case -1:
            perror("fork error");
            exit(-1);
            break;
        default: ;// macierzysty
            break;
        }
    }


for (int i = 0; i < 5; i++) {
            int status;

            if ((wait(&status)) == -1) {
                perror ("wait error");
                exit(EXIT_FAILURE);
            }
            if (WIFSIGNALED(status)) {
                printf("Proces zakończony sygnałem nr %d o nazwie '%s'.\n", WTERMSIG(status), strsignal(WTERMSIG(status)));
            } else {
                printf("Proces zakończony z kodem wyjścia %d.\n", WEXITSTATUS(status));
            }
}

    exit(EXIT_SUCCESS);
}