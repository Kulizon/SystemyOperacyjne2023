#include "memLib.h"


int shmemory_open(char *name, int flags) {
    int descryptor;

    if((descryptor = shm_open(name, flags, 0644)) == -1){
        perror("SHM_OPEN ERROR -> SHMEMORY_OPEN()\n");
        _exit(EXIT_FAILURE);
    }

    return descryptor;
}
 

void shmemory_set(int fd, off_t lenght){
    if(ftruncate(fd, lenght) == -1){
        perror("FTRUNCATE ERROR -> SHMEMORY_SET()\n");
        exit(EXIT_FAILURE);
    }
}

void shmemory_close(int fd){
    if(close(fd) == -1){
        perror("CLOSE ERROR -> SHMEMORY_CLOSE()\n");
        exit(EXIT_FAILURE);
    }
}

void shmemory_unlink(char *name){
    if(shm_unlink(name) == -1)
    {
        perror("SHM_UNLINK ERROR -> SHMEMORY_UNLINK()\n");
        exit(EXIT_FAILURE);
    }
}

void *memory_map(void *addr, size_t lenght, int prot, int flags, int fd, off_t offset){
    void *ret;

    if((ret = mmap(addr, lenght, prot, flags, fd, offset)) == MAP_FAILED)
    {
        perror("MMAP ERROR -> MEMORY_MAP()\n");
        exit(EXIT_FAILURE);
    }

    return ret;
}

void memory_unlink_map(void *addr, size_t lenght){
    if(munmap(addr, lenght) == -1){
        perror("MUNMAP ERROR -> MEMORY_UNLINK_MAP()\n");
        exit(EXIT_FAILURE);
    }
}