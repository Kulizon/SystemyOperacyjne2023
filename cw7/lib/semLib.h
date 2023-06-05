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

sem_t* create_sem(char semName[], int value);
void unlink_sem(char semName[]);
sem_t* read_sem(char semName[]);
void wait_sem(sem_t* sem);
void unlock_sem(sem_t* sem);
int get_value_sem(sem_t* sem);

#endif


