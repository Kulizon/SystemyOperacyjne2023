#ifndef SIMPLE_LIB
#define SIMPLE_LIB

#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

#define SEM_NAME "semafor"

sem_t* create_sem();
int unlink_sem();
sem_t* read_sem();
int wait_sem(sem_t* sem);
int unlock_sem(sem_t* sem);
int get_value_sem(sem_t* sem);

#endif


