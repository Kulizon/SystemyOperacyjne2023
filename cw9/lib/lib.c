#include "lib.h"


pthread_t create_pt(void (*callback) (void *), void* arg) {
    pthread_t id;

    if (pthread_create(&id, NULL, callback, arg) != 0) {
        perror("Error creating pt");
        exit(EXIT_FAILURE);
    }

    return id;
}

void end_pt() {
    int status;
    pthread_exit(&status);
}

void join_pt(pthread_t id) {
    if (pthread_join(id, NULL) != 0) {
        perror("Error joining pt");
        exit(EXIT_FAILURE);
    }
    
}

void detach_pt(pthread_t id) {
    if (pthread_detach(id) != 0) {
        perror("Error detaching pt");
        exit(EXIT_FAILURE);
    }   
}


void lock_m(pthread_mutex_t *m) { // blokuje watek ktory wywola te funckje
    if (pthread_mutex_lock(m) != 0) {
        perror("Error locking m");
        exit(EXIT_FAILURE);
    }
}

void try_lock_m(pthread_mutex_t *m) { // nie blokuje watku
    if (pthread_mutex_trylock(m) != 0) {
        perror("Error trying to lock m");
        exit(EXIT_FAILURE);
    }
}

void open_m(pthread_mutex_t *m) {
    if (pthread_mutex_unlock(m) != 0) {
        perror("Error opening m");
        exit(EXIT_FAILURE);
    }
}

void destroy_m(pthread_mutex_t *m) {
    if (pthread_mutex_destroy(m) != 0) {
        perror("Error destroying m");
        exit(EXIT_FAILURE);
    }
}