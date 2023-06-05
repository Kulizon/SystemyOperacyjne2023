#include "lib/lib.h"
#include "header.h"
#include <limits.h>

mqd_t des_serv;
mqd_t des_rec;

void exitHandler() {
    close_que(des_rec);
    close_que(des_serv);
    remove_que(SERVER_QUE_NAME);
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

    struct mq_attr attr;    
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10; // Maximum number of messages in the queue
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;


    // utworz kolejke komunikatow w trybie do odbierania
    des_serv = open_que(SERVER_QUE_NAME, O_CREAT | O_RDONLY, 0644, &attr);

    printf("Nazwa kolejki serwera: %s\n", SERVER_QUE_NAME);
    printf("Atrybuty kolejki serwera: mq_flags: %ld, mq_maxmsg: %ld, mq_msgsize: %ld, mq_curmsgs: %ld\n", attr.mq_flags, attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);
    printf("Deskryptor kolejki serwera: %d\n", des_serv);


    while (1)
    {
        // odbierz komunikat od klienta
        char buffer[MAX_MSG_SIZE + 1];
        int bytes = get_from_que(des_serv, buffer, MAX_MSG_SIZE, NULL);
        buffer[bytes] = '\0';

        char pid[10]; 
        char operation[MAX_MSG_SIZE]; 
        char num1[10], num2[10]; 

        if (sscanf(buffer, "/%9[^ ] %19[^ ] %9[^ ] %9[^ ]", pid, num1, operation, num2) != 4) {
            perror("Invalid input format.\n");
            break;
        }

        if (strcmp(operation, "+") != 0 &&  strcmp(operation, "-") != 0 && strcmp(operation, "*") != 0 && strcmp(operation, "/") != 0) {
            perror("Invalid operation.\n");
            break;
        }

        printf("Odebrano polecenie '%s %s %s' od procesu o PID: '%s'\n", num1, operation, num2, pid);

        sleep(rand() % 2 + 1);

        char dest_que_name[12];
        sprintf(dest_que_name, "/%s", pid);
        des_rec = open_que(dest_que_name, O_WRONLY, 0644, &attr);

        char res[MAX_MSG_SIZE];
        int ans = INT_MIN;
        if (strcmp(operation, "+") == 0) {
            ans = atoi(num1) + atoi(num2);
        } else if (strcmp(operation, "-") == 0) {
            ans = atoi(num1) - atoi(num2);
        } else if (strcmp(operation, "*") == 0) {
            ans = atoi(num1) * atoi(num2);
        } else if (strcmp(operation, "/") == 0) {
            if (atoi(num2) == 0) {
                ans = INT_MIN;
            } else{
                ans = atoi(num1) / atoi(num2);
            }
        }
        
        sleep(rand() % 2 + 1);

        sprintf(res, "%d", ans);
        send_to_que(des_rec, res, strlen(res), 0);

        printf("Wysłano komunikat '%s' do procesu '%s'\n", res, pid);

        close_que(des_rec);

        sleep(1);
    }
    

    exit(EXIT_SUCCESS);
}
