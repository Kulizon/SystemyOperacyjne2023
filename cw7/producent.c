#include "lib/semLib.h"
#include "lib/memLib.h"
#include <string.h>

#define CHUNK 16

typedef struct {
    char bufor[NBUF][NELE]; 
    int wstaw, wyjmij; 
} shm_segment;

int main(int argc, char *argv[]) {
    
    int memory_descryptor = shmemory_open(argv[1], O_RDWR); // memory_descryptor deskryptor do pamieci dzielonej

    shm_segment *prodMem = (shm_segment *)memory_map(NULL, sizeof(shm_segment), PROT_WRITE, MAP_SHARED, memory_descryptor, 0);
    prodMem->wstaw = 0;    //inicjalizacja wstaw
    prodMem->wyjmij = 0;   //inicjalizacja wyjmij

    sem_t* prodSem = read_sem(argv[2]);
    sem_t* konsSem = read_sem(argv[3]); // Semafor do wstrzymywania Konsumenta

    int prodVal; 
    //int konsVal; 

    printf("=== producent.c ===\n");
    printf("Adres semafora producenta: %p\n", (void*) prodSem);
    printf("Adres semafora konsumenta: %p\n", (void*)konsSem);
    printf("Deskryptor dzielonej pamięci: %d\n", memory_descryptor);
    printf("Rozmiar dzielonej pamięci: %ld\n\n", sizeof(shm_segment));

    char* srcFileName = argv[4];

    size_t source = open(srcFileName, O_RDONLY);
    if (source == -1) {
        perror("OPENING IN/OUT FILES ERROR\n");
        exit(EXIT_FAILURE);
    }

    int bytesRead;
    char towar[CHUNK];  
    memset(towar, 0, NELE);    //inicjalizacja tablicy towar

    while (1) {
        // czekaj na semafor
        wait_sem(prodSem);

        sleep(rand() % 2 + 1);
        bytesRead = read(source, towar, CHUNK);   //czytanie do "towar" z pliku ciagu znakow
        if(bytesRead == -1){
            printf("SOURCE READ ERROR");
            break;
        }

        if(bytesRead == 0){         //jesli bytes == 0 oznacza to ze nasz read nic nie przeczytal (skoczyly sie znaki)
            printf("Koniec pracy producenta\n");
            unlock_sem(konsSem);
            strcpy(prodMem->bufor[prodMem->wstaw], "\0");     //przekazanie do tablicy w pamieci znaku "\0" ktory zakonczy konsumenta
            break;
        }
        prodVal = get_value_sem(prodSem);
        printf("\tProducent:  Wartość semafora: %d | Indeks bufora: %d | Towar: '%s' | Rozmiar towaru: %ld\n", prodVal, prodMem->wstaw, towar, strlen(towar));
        strcpy(prodMem->bufor[prodMem->wstaw], towar);    //do bufora w pamieci umieszczamy towar pobrany przez read
        
        prodMem->wstaw = (prodMem->wstaw + 1) % NBUF;     //przesuniecie pozycji wstawiania o 1
        memset(towar, 0, CHUNK);     //czyszczenie tablicy towar

        // odblokowanie semaforu konsumenta
        unlock_sem(konsSem);
    }

    // zamknij plik zrodlowy
    if (close(source) == -1) { 
        perror ("ERROR CLOSING FILE\n");
        exit (EXIT_FAILURE);
    }

    memory_unlink_map(prodMem, sizeof(shm_segment));
    shmemory_close(memory_descryptor);

    exit(EXIT_SUCCESS);
}
