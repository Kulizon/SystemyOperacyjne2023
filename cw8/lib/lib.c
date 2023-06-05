#include "lib.h"


mqd_t open_que(char name[], int flags, int mode, struct mq_attr* attr){
    mqd_t output = mq_open(name, flags, mode, attr);
    if (output == -1) {
        perror("Error opening mq");
        exit(EXIT_FAILURE);
    }

    return output;
}

void close_que(mqd_t des) {
    if (mq_close(des) == -1) {
        perror("Error closing mq");
        exit(EXIT_FAILURE);
    }
}

void remove_que(char name[]) {
    if (mq_unlink(name) == -1) {
        perror("Error unlinking mq");
        exit(EXIT_FAILURE);
    }
}

void send_to_que(mqd_t des, char msg[], int msgLen, unsigned int msgPrio) {
    if (mq_send(des, msg, msgLen, msgPrio) == -1) {
        perror("Error sending to mq");
        exit(EXIT_FAILURE);
    }
}

int get_from_que(mqd_t des, char msg[], int msgLen, unsigned int* msgPrio) {
    int bytes = mq_receive(des, msg, msgLen, msgPrio); 
    if (bytes == -1) {
        perror("Error getting from mq");
        exit(EXIT_FAILURE);
    }
    return bytes;
}



// proces tworzy kolejke komunikatow - mqd t mq open(const char *name, int oflag);O RDWR, O CREAT

// inny proces ktory chce z niej skorzystac musi ja otworzyc - mqd t mq open(const char *name, int oflag); (inna flaga) O RDONLY, O WRONLY

// wysylanie komunikatow do/z kolejki miedzy procesami - int mq send(mqd t mqdes, const char *msg ptr, size t msg len, unsigned int msg prio);
// int mq receive(mqd t mqdes, char *msg ptr, size t msg len, unsigned int *msg prio);

// zamykanie kolejki gdy nie jest juz uzywana 
// gdy nie jest juz potrzebna nalezy usunac kolejke


// ! Uwaga: Aby mo˙zna by lo u˙zywa´c powy˙zszych kolejek komunikat´ow w programach w języku C należy je linkować z opcją -lrt


