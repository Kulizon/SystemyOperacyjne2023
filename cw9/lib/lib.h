
#define _REENTRANT
#include <pthread.h>

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
#include <string.h>


pthread_t create_pt(void (*callback) (void *), void *arg);

void end_pt();

void join_pt(pthread_t id);
void detach_pt(pthread_t id);
void lock_m(pthread_mutex_t *m);
void try_lock_m(pthread_mutex_t *m);
void open_m(pthread_mutex_t *m);
void destroy_m(pthread_mutex_t *m);