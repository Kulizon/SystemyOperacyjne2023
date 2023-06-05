#include "semLib.h"

sem_t* create_sem(char semName[], int value) {
    sem_t* sem; // utworzenie semaforu


    // add later : | O_EXCL
    if ((sem = sem_open(semName, O_CREAT | O_EXCL, 0644, value)) == SEM_FAILED) {
        perror ("Error creating semaphor");
        exit(EXIT_FAILURE);
    }

    return sem;
}

void unlink_sem(char semName[]) {
    if (sem_unlink(semName) == -1) { // usuowanie semafora
        perror ("Error calling sem_unlink - unlinking semaphor");
    };
}

sem_t* read_sem(char semName[]) {
    // otwarcie semaforu do odczytu
    sem_t* sem;
    
    if ((sem = sem_open(semName, 0)) == SEM_FAILED) {
        perror ("Error opening semaphor to read");
        exit(EXIT_FAILURE);
    }

    return sem;
}

void wait_sem(sem_t* sem) {
    // czekanie na swoja kolej
    if (sem_wait(sem) == -1) {
        perror ("Error waiting for semaphore");
        exit(EXIT_FAILURE);
    }
}

void unlock_sem(sem_t* sem) { // otwarcie semaforu do odczytu
    if (sem_post(sem) == -1) {
        perror ("Error calling sem_post - unlocking semaphor");
        exit(EXIT_FAILURE);
    };
}

int get_value_sem(sem_t* sem) { // otwarcie semaforu do odczytu
    int val;

    if (sem_getvalue(sem, &val) == -1) {
        perror ("Error calling sem value");
        exit(EXIT_FAILURE);
    };

    return val;
}
