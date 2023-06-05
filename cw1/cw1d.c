#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int printOutInfo() {
    int uid = getuid();
    int gid = getgid();
    int pid = getpid();
    int ppid = getppid();
    int pgid = __getpgid(pid);
    
    printf("UID: %d | ", uid);
    printf("GID: %d | ", gid);
    printf("PID: %d | ", pid);
    printf("PPID: %d | ", ppid);
    printf("PGID: %d \n", pgid);
    return 0;
}

int main() {
    printOutInfo();

    for (int i = 0; i < 3; i++)
    {
        pid_t pid = fork();

        switch (pid)
        {
        case 0:
            sleep(2); 
            printOutInfo();
            break;
        case -1:
            perror("fork error");
            exit(-1);
            break;
        default:
            break;
        }
    }

    sleep(4); 

    return 0;
}