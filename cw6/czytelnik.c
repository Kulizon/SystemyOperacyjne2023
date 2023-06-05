#include "lib/lib.h"

#define NUM_PATH "./numer.txt"
#define CHUNK 4

//
//
// sekca krytyczna - obszar w ktorym proces korzysta z semaforu
//
//

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Argc: %d", argc);
        perror("Too little arguments 2");
        _exit(EXIT_FAILURE);
    }

    int sectionNum = atoi(argv[1]);

    sem_t* sem = read_sem();
    int semVal = get_value_sem(sem);
    printf("Pid procesu: %d\n", getpid());
    printf("Wartość semafora przed sekcją krytyczną: %d\n", semVal);

    for (int i = 0; i < sectionNum; i++) {
        // czekaj na semafor
        wait_sem(sem);

        semVal = get_value_sem(sem);
        printf("    Sekcja krytyczna nr.%d procesu o PID: %d\n", i + 1, getpid());
        printf("    Wartość semafora w trakcie sekcji krytycznej: %d\n", semVal);

        // logic
        size_t source = open(NUM_PATH, O_RDONLY);
        if (source == -1) {
            perror("OPENING IN/OUT FILES ERROR\n");
            _exit(EXIT_FAILURE);
        }

        int bytesRead;
        char buffer[CHUNK];

        while ((bytesRead = read(source, buffer, CHUNK))) {
                if(bytesRead == -1) {
                    perror("READ ERROR\n");
                    _exit(EXIT_FAILURE);
                }      
        }

        printf("    Odczytana wartość z pliku: %d\n", atoi(buffer));

        sleep(rand() % 2 + 1);

        // zamknij plik jako plik do oczytu
        if (close(source) == -1) { 
            perror ("ERROR CLOSING FILE\n");
            exit (EXIT_FAILURE);
        }

        // otworz plik do zapisu
        size_t dest = open(NUM_PATH, O_WRONLY, 0644);
        if (dest == -1) {
            perror("OPENING IN/OUT FILE ERROR\n");
            _exit(EXIT_FAILURE);
        }

        int newVal = atoi(buffer) + 1;

        printf("    Zapisana wartość do pliku: %d\n\n", newVal);

        char newStrVal[12];
        sprintf(newStrVal, "%d", newVal);

        // zapisz wartosc zwiekszona o 1
        int bytesWritten = write(dest, newStrVal, CHUNK);

        if (bytesWritten == -1) {
            perror("WRITE ERROR\n");
            _exit(EXIT_FAILURE);
        }

        if (close(dest) == -1) {
            perror ("ERROR CLOSING FILE\n");
            exit (EXIT_FAILURE);
        }

        // unlock semaphor 
        unlock_sem(sem);

        sleep(rand() % 2 + 1);
    }



    semVal = get_value_sem(sem);
    printf("Wartość semafora po sekcji: %d\n\n", semVal);
    
    sleep(rand() % 2 + 1);
    _exit(EXIT_SUCCESS);
}





