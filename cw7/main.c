#include "lib/semLib.h"
#include "lib/memLib.h"
#include <signal.h>
#include <sys/wait.h>

#define SEM_KONS_NAME "kons"
#define SEM_PROD_NAME "prod"
#define SHM_NAME "/shm"

typedef struct {
    char bufor[NBUF][NELE]; 
    int wstaw, wyjmij; 
} shm_segment;

sem_t* prodSem = NULL;
sem_t* konsSem = NULL;  

int memory_descryptor = -1;

void exitHandler() {
    unlink_sem(SEM_KONS_NAME);
    unlink_sem(SEM_PROD_NAME);
    sem_close(prodSem);
    sem_close(konsSem);
    shmemory_unlink(SHM_NAME);
    shmemory_close(memory_descryptor);
}

int main(int argc, char *argv[]) {
    // char* producerPath = argv[1];
    // char* consumerPath = argv[2];

    if (argc != 5) {
        perror("Zły format, sprawdź README.md");
        exit(EXIT_FAILURE);
    }

    if(atexit(exitHandler) != 0) {
        perror("ATEXIT ERROR\n");
        exit(EXIT_FAILURE);
    }

    if(signal(SIGINT, exitHandler) == SIG_ERR) {
        perror("SIGNAL ERROR\n");
        exit(EXIT_FAILURE);
    }
    
    // utworz semafor producenta i konsumenta
    prodSem = create_sem(SEM_PROD_NAME, 1);
    konsSem = create_sem(SEM_KONS_NAME, 0);  

    // utworz pamiec dzielona
    memory_descryptor = shmemory_open(SHM_NAME, O_CREAT | O_EXCL | O_TRUNC | O_RDWR);
    shmemory_set(memory_descryptor, sizeof(shm_segment));

    printf("=== main.c ===\n");
    printf("Adres semafora producenta: %p\n", (void*) prodSem);
    printf("Adres semafora konsumenta: %p\n", (void*)konsSem);
    printf("Deskryptor dzielonej pamięci: %d\n", memory_descryptor);
    printf("Rozmiar dzielonej pamięci: %ld\n\n", sizeof(shm_segment));


    for (int i = 0; i < 2; i++) { // stworzenie dwa procesy - producenta i konsumenta
        int pid = fork();

        switch (pid) {
        case 0: // potomny
            // argv[1] - producer, argv[2] - consumer
            if( execlp(argv[i+1], argv[i+1], SHM_NAME, SEM_PROD_NAME, SEM_KONS_NAME, i == 0 ? argv[3] : argv[4], (char *) NULL) == -1) {
                perror("execlp error 2");
                exit(EXIT_FAILURE);
            }
            
            break;
        case -1:
            perror("fork error");
            exit(EXIT_FAILURE);
        default: // macierzysty
            break;
        }
    }

    for (int i = 0; i < 2; i++) {
        wait(NULL);
    } 

    exit(EXIT_SUCCESS); // wywolanie funkcji atexit
}
