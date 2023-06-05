#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <mqueue.h>
#include <string.h>

mqd_t open_que(char name[], int flags, int mode, struct mq_attr* attr);
void send_to_que(mqd_t des, char msg[], int msgLen, unsigned int msgPrio);
int get_from_que(mqd_t des, char msg[], int msgLen, unsigned int* msgPrio);
void close_que(mqd_t des);
void remove_que(char name[]);