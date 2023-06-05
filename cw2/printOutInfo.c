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
    return 0;
}