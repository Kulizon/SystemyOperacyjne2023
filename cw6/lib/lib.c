#include "lib.h"

sem_t* create_sem() {
    sem_t* sem; // utworzenie semaforu


    // add later : | O_EXCL
    if ((sem = sem_open(SEM_NAME, O_CREAT | O_EXCL, 0644, 0)) == SEM_FAILED) {
        perror ("Error creating semaphor");
        exit(EXIT_FAILURE);
    }

    return sem;
}

int unlink_sem() {
    if (sem_unlink(SEM_NAME) == -1) { // usuowanie semafora
        perror ("Error calling sem_unlink - unlinking semaphor");
        exit(EXIT_FAILURE);
    };
}

sem_t* read_sem() {
    // otwarcie semaforu do odczytu
    sem_t* sem;
    
    if ((sem = sem_open(SEM_NAME, 0)) == SEM_FAILED) {
        perror ("Error opening semaphor to read");
        exit(EXIT_FAILURE);
    }

    return sem;
}

int wait_sem(sem_t* sem) {
    // czekanie na swoja kolej
    if (sem_wait(sem) == -1) {
        perror ("Error waiting for semaphore");
        exit(EXIT_FAILURE);
    }
}

int unlock_sem(sem_t* sem) { // otwarcie semaforu do odczytu
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
