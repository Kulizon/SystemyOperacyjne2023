#ifndef SHARED_MEM_LIB   
#define SHARED_MEM_LIB

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>

#define NELE 20 // NELE rozmiar elementu bufora (jednostki towaru w bajtach)
#define NBUF 5 // NBUF liczba elementow bufora

int shmemory_open(char *name, int flags);
void shmemory_set(int fd, off_t lenght);
void shmemory_close(int fd);
void shmemory_unlink(char *name);
void *memory_map(void *addr, size_t lenght, int prot, int flags, int fd, off_t offset);
void memory_unlink_map(void *addr, size_t lenght);


#endif