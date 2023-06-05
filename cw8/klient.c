#include "./lib/lib.h"
#include "header.h"
#include <limits.h>

mqd_t des_serv;
mqd_t des_rec;
char que_name[10];

void exitHandler() {
    close_que(des_rec);
    close_que(des_serv);
    remove_que(que_name);
}

int main(int argc, char *argv[]) {
    if(atexit(exitHandler)!= 0) {
        perror("ATEXIT ERROR\n");
        exit(EXIT_FAILURE);
    }

    if(signal(SIGINT, exitHandler) == SIG_ERR) {
        perror("SIGNAL ERROR\n");
        exit(EXIT_FAILURE);
    }
    
    int pid = getpid();
    sprintf(que_name, "/%d", pid);

    struct mq_attr attr;    
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10; // max number of messages in the queue
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    des_rec = open_que(que_name, O_CREAT | O_RDONLY, 0644, &attr);

    printf("Nazwa kolejki klienta '%d': %s\n", pid, que_name);
    printf("Atrybuty kolejki klienta '%d': mq_flags: %ld, mq_maxmsg: %ld, mq_msgsize: %ld, mq_curmsgs: %ld\n", pid, attr.mq_flags, attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);
    printf("Deskryptor kolejki klienta '%d': %d\n", pid, des_rec);
    
    sleep(1);

    // otworz kolejke serwera do nadawania komunikatow
    des_serv = open_que(SERVER_QUE_NAME, O_WRONLY, 0644, &attr);

    // petla i wczytuj zadania z klaiwatury, wysylaj swoj pid i zadanie na serwer
    printf("Należy wpisywać operacje w formacie 'liczba1 znak liczba2', zostaną one obliczone na serwerze i zwrócone.\n");
    char input[MAX_MSG_SIZE];
    while (1) { // change later to "endofline"
        fgets(input, sizeof(input), stdin);

        if (feof(stdin)) {
            printf("Koniec działania!\n");
            break;
        }

        char operation[2]; 
        char num1[10], num2[10]; 

        if (sscanf(input, "%9[^ ] %9[^ ] %9[^ ]", num1, operation, num2) != 3) {
            printf("Nieprawidłowy format.\n");
            memset(num1, 0, sizeof(num1));
            memset(operation, 0, sizeof(operation));
            memset(num2, 0, sizeof(num2));
            continue;
        }

        if (strcmp(operation, "+") != 0 &&  strcmp(operation, "-") != 0 && strcmp(operation, "*") != 0 && strcmp(operation, "/") != 0) {
            printf("Nieprawidłowa operacja.\n");
            memset(num1, 0, sizeof(num1));
            memset(operation, 0, sizeof(operation));
            memset(num2, 0, sizeof(num2));
            continue;
        }

        printf("Przyjęto operację: %s %s %s", num1, operation, num2);
        char msg[MAX_MSG_SIZE + 11];
        input[strcspn(input, "\n")] = '\0'; // usun \n z input
        sprintf(msg, "%s %s", que_name, input);
        printf("Wysłano '%s' na serwer\n", msg);
        send_to_que(des_serv, msg, strlen(msg) + 1, 0);

        char buffer[MAX_MSG_SIZE + 1];
        int bytes = get_from_que(des_rec, buffer, MAX_MSG_SIZE, NULL);
        buffer[bytes] = '\0';
        
        printf("Odebrano '%s' z serwera\n", buffer);

        int ans = INT_MIN;
        if (strcmp(operation, "+") == 0) {
            ans = atoi(num1) + atoi(num2);
        } else if (strcmp(operation, "-") == 0) {
            ans = atoi(num1) - atoi(num2);
        } else if (strcmp(operation, "*") == 0) {
            ans = atoi(num1) * atoi(num2);
        } else if (strcmp(operation, "/") == 0) {
            if (atoi(num2) == 0) {
                ans =  INT_MIN;
            } else{
                ans = atoi(num1) / atoi(num2);
            }
        }

        if (atoi(buffer) != ans) {
            printf("Coś poszło nie tak - wyniki się nie zgadzają...\n");
        } else {
            printf("Wszystko okej - wyniki się zgadzają...\n");
        }
    }

    

    exit(EXIT_SUCCESS);
}
