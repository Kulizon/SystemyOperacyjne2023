#include "lib/lib.h"
#include <signal.h>
#include <sys/wait.h>

#define NUM_PATH "./numer.txt"
#define NUM_NAME "numer.txt"
#define CHUNK 4

void exitHandler() {
    unlink_sem();
}

int main(int argc, char *argv[]) {
    // argumenty programu: (nazwa czytelnika) (liczba procesów) (liczba sekcji krytycznych 1) (liczba sekcji krytycznych 2) ...
    
    char* readerPath = argv[1];
    int argsOffset = 3;

    if (argc < argsOffset) {
        perror("Too little arguments 1");
        exit(EXIT_FAILURE);
    }

    int numOfPrograms = atoi(argv[2]);

    // sprawdzaczenie czy podano odpowednia ilosc sekcji krytycznych do wybranej ilosci programow
    if (argc - argsOffset < numOfPrograms) {
        perror("Too little arguments 3");
        exit(EXIT_FAILURE);
    } 
    if (argc - argsOffset > numOfPrograms) {
        perror("Too much arguments 1");
        exit(EXIT_FAILURE);
    }

    if(atexit(exitHandler)!= 0)
    {
        perror("ATEXIT ERROR\n");
        exit(EXIT_FAILURE);
    }

    if(signal(SIGINT, exitHandler) == SIG_ERR) {
        perror("SIGNAL ERROR\n");
        exit(EXIT_FAILURE);
    }
    
    // utworz semafor
    sem_t* sem = create_sem();
    unlock_sem(sem);
    sleep(1);
    printf("\nAdres semafora: %p\n", (void*)sem);
    int val = get_value_sem(sem);
    printf("Wartość semafora: %d\n\n", val);

    // stworz plik tesktowy numer.txt, wpisz w nim "0"
    // otworz plik do zapisu
    size_t dest = open(NUM_NAME, O_WRONLY | O_CREAT, 0644);
    if (dest == -1) {
        perror("OPENING IN/OUT FILE ERROR\n");
        exit(EXIT_FAILURE);
    }

    int newVal = 0;
    char newStrVal[12];
    sprintf(newStrVal, "%d", newVal);

    int bytesWritten = write(dest, newStrVal, CHUNK);

    if (bytesWritten == -1) {
        perror("WRITE ERROR\n");
        exit(EXIT_FAILURE);
    }

    if (close(dest) == -1) {
        perror ("ERROR CLOSING FILE\n");
        exit (EXIT_FAILURE);
    }

    // programy uzywajace semaforow - odycztuja numer.txt i dodaja 1 do zapisanego numeru

    int goal = 0;
    for (int i = 0; i < numOfPrograms; i++) { // stworzenie dwoch procesow korzystajacych z jednego zasobu 
    
        // numer jaki ma być w pliku to suma liczby sekcji krytycznych
        goal += atoi(argv[i + argsOffset]);
        int pid = fork();

        switch (pid)
        {
        case 0: // potomny
            // utworz czytelnikow
            
            if( execlp(readerPath, readerPath, argv[i + argsOffset], (char *) NULL) == -1) {
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

    for (int i = 0; i < numOfPrograms; i++) {
        wait(NULL);
    }
    
    
    // sprawdzenie poprawnosci wykonania programow


    size_t source = open(NUM_PATH, O_RDONLY);
    if (source == -1) {
        perror("OPENING IN/OUT FILES ERROR\n");
        exit(EXIT_FAILURE);
    }

    int bytesRead;
    char buffer[CHUNK];

    while ((bytesRead = read(source, buffer, CHUNK))) {
            if(bytesRead == -1) {
                perror("READ ERROR\n");
                exit(EXIT_FAILURE);
            }        
    }

    // zamknij plik jako plik do oczytu
    if (close(source) == -1) { 
        perror ("ERROR CLOSING FILE\n");
        exit (EXIT_FAILURE);
    }

    int output = atoi(buffer);

    if (goal != output) {
        printf("Coś poszło nie tak! Miało być (%d), a jest(%d)!\n", goal, output);
    } else {
        printf("Wszystko w porządku! Miało być (%d) i jest (%d)!\n", goal, output);
    }

    exit(EXIT_SUCCESS);
}
