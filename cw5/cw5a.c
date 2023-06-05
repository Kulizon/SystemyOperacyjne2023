#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>

#define FIFO_NAME "./potok.FIFO"

void exitHandler() {
    if(unlink(FIFO_NAME) == -1) {
        perror("UNLINK ERROR\n");
        _exit(EXIT_FAILURE);   
    }
    else {
        printf("Zamknięto potok\n");
    }
}

int main (int argc, char *argv[]) {
    char *inFilePath = argv[1];
    char *outFilePath = argv[2];
    char *producerFilePath = argv[3];
    char *consumerFilePath = argv[4];


    if(mkfifo(FIFO_NAME, 0644) == -1)
    {
        perror("MKFIFO ERROR\n");
        _exit(EXIT_FAILURE);
    }

    if(atexit(exitHandler)!=0)
    {
        perror("ATEXIT ERROR\n");
        exit(EXIT_FAILURE);
    }

    if(signal(SIGINT, exitHandler) == SIG_ERR) {
        perror("SIGNAL ERROR\n");
        exit(EXIT_FAILURE);
    }

    // printf ("Otwarto potok nazwany z deskryptorami: %d, %d\n", despipe[0], despipe[1]);

    for (int i = 0; i < 2; i++)
    {
        pid_t pid = fork();
        switch (pid) {
            case 0: ;
                if (i == 0) {
                    printf("pid: %d, path: %s\n", pid, producerFilePath);

                    if( execlp(producerFilePath, producerFilePath, inFilePath, FIFO_NAME, (char *) NULL) == -1) {
                        perror("execlp error 1 ");
                        exit(EXIT_FAILURE);
                    }
                }
                
                if (i == 1) {

                    printf("pid: %d, path: %s\n", pid, consumerFilePath);

                    if( execlp(consumerFilePath, consumerFilePath, outFilePath, FIFO_NAME, (char *) NULL) == -1) {
                        perror("execlp error 2");
                        exit(EXIT_FAILURE);
                    }
                    break;
 
                }

                break;
            case -1: // błąd
                perror("fork error");
                exit(-1);
                break;
            default: // macierzysty
                break;
        }
    }
    
    for(int i = 0; i<2; i++)
    {
        if(wait(NULL) == -1)
        {
            perror("WAIT ERROR\n");
            exit(EXIT_FAILURE);
        }
    }
    
    
    return 0;
}