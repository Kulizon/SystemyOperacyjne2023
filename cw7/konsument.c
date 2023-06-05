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

    shm_segment *konsMem = (shm_segment *)memory_map(NULL, sizeof(shm_segment), PROT_WRITE, MAP_SHARED, memory_descryptor, 0);
    konsMem->wstaw = 0;    //inicjalizacja wstaw
    konsMem->wyjmij = 0;   //inicjalizacja wyjmij

    sem_t* prodSem = read_sem(argv[2]);
    sem_t* konsSem = read_sem(argv[3]); // Semafor do wstrzymywania Konsumenta

    //int prodVal; 
    int konsVal; 

    printf("=== konsument.c ===\n");
    printf("Adres semafora producenta: %p\n", (void*) prodSem);
    printf("Adres semafora konsumenta: %p\n", (void*)konsSem);
    printf("Deskryptor dzielonej pamięci: %d\n", memory_descryptor);
    printf("Rozmiar dzielonej pamięci: %ld\n\n", sizeof(shm_segment));

    char* destFileName = argv[4];

    size_t dest = open(destFileName, O_WRONLY);
    if (dest == -1) {
        perror("OPENING IN/OUT FILES ERROR\n");
        exit(EXIT_FAILURE);
    }

    int bytesWritten;
    char towar[CHUNK];  
    memset(towar, 0, NELE);    //inicjalizacja tablicy towar

    while (1) {
        // czekaj na semafor
        wait_sem(konsSem);

        sleep(rand() % 2 + 1);
        strcpy(towar, konsMem->bufor[konsMem->wyjmij]);

        if(strcmp(towar, "\0") == 0){       //jesli towar i "\0" beda takie same, konczymy program (taka wiadomosc wysyla producent kiedy zakonczy produkcje)
            printf("Koniec pracy konsumenta\n");
            break;
        }

        konsVal = get_value_sem(konsSem);
        printf("\tKonsument: Wartość semafora: %d | Indeks bufora: %d | Towar: '%s' | Rozmiar towaru: %ld\n", konsVal, konsMem->wyjmij, towar, strlen(towar));
       
        konsMem->wyjmij = (konsMem->wyjmij + 1) % NBUF;   //przesuniecie pozycji wyjmowania o 1

        bytesWritten = write(dest, towar, sizeof(char)*strlen(towar));    //wpisanie ciagu znakow do pliku

        if (bytesWritten == -1) {
            printf("WRITE TO FILE ERROR");
            break;
        }

        memset(towar, 0, CHUNK);     //wyczyszczenie tablicy towar

        unlock_sem(prodSem);
    }

    // zamknij plik zrodlowy
    if (close(dest) == -1) { 
        perror ("ERROR CLOSING FILE\n");
        exit (EXIT_FAILURE);
    }

    memory_unlink_map(konsMem, sizeof(shm_segment));
    shmemory_close(memory_descryptor);

    exit(EXIT_SUCCESS);
}
