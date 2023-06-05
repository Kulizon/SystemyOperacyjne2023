#include "lib/lib.h"

void usleep (int time);

int global_counter = 0;
// utworz muteks
pthread_mutex_t myMutex = PTHREAD_MUTEX_INITIALIZER;
int thread_num = -1; // liczba wątków
int section_num = -1; // liczba sekcji krytycznych wątków

void exitHandler() {
    destroy_m(&myMutex);
}

// czy musi być???

// Do wypisywania komunikatów o błędach funkcji wątkowych odpowiadających zwracanym przez 
// nie kodom błędów w przypadku porażki użyć funkcji strerror() (patrz podrozdział 1.2 w materiałach nt. procesów).

void gotoxy(unsigned x, unsigned y)
{
  printf("\033[%d;%dH\033[2K", y, x);
}

void thread_callback(void *arg) {
    int counter = 0;   
    int thread_i = *(int*)arg;   // indeks wątku

    sleep(rand() % 2  + 1);
    
    for (int i = 0; i < section_num; i++)
    {
        gotoxy(0, thread_num + thread_i + 5); // sekcja prywatna
        printf("Indeks wątku: %d ", thread_i);   //wypisz index watku
        printf("Sekcja prywatna nr %d", i + 1);   //wypisz numer sekcji prywatnej

        gotoxy(0, thread_num + 3);
        printf("\n----------------Licznik = %d----------------\n", global_counter);

        sleep( rand() % 2  + 1);

        // sekcja krytyczna
		lock_m(&myMutex);

        counter = global_counter;
        counter++;

        gotoxy(40, thread_num + thread_i + 5); // sekcja krytyczna
        printf("Indeks wątku: %d ", thread_i);   //wypisz index watku
        printf("Sekcja krytyczna nr %d", i + 1); // wypisz numer sekcji krytycznej

        global_counter = counter;
        gotoxy(0, thread_num + 3);
        printf("\n----------------Licznik = %d----------------\n", global_counter);

        sleep( rand() % 2  + 1);

        // koniec sekcji krytycznej
        open_m(&myMutex);
        fflush(stdout);
    }
    
    // wypisz koniec pracy watku
    gotoxy(0, thread_num + thread_i + 5);
    printf("Koniec pracy wątku nr %d!", thread_i);   //wypisz sekcje prywatna i jej numer
    sleep(rand() % 2  + 1);

}


int main(int argc, char *argv[]) { 
    thread_num = atoi(argv[1]); // liczba wątków
    section_num = atoi(argv[2]); // liczba sekcji krytycznych wątków

    sleep(2);

    if (argc != 3 || thread_num <= 0 || section_num <= 0) {
        perror("Złe argumenty wywołania programu. Patrz README.");
        exit(EXIT_FAILURE);
    }


    if(atexit(exitHandler)!= 0) {
        perror("ATEXIT ERROR\n");
        exit(EXIT_FAILURE);
    }

    if(signal(SIGINT, exitHandler) == SIG_ERR) {
        perror("SIGNAL ERROR\n");
        exit(EXIT_FAILURE);
    }

    // Wyczysc ekran
    if (system("clear") == -1) {
        perror("Error in call to system() function");
        exit(EXIT_FAILURE);
    }

    srand(123);  // inicjalizacja generatora liczb losowych

    printf("Adres utworzonego muteksu: %p\n", (void *)&myMutex);

    pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t)*thread_num);  //tablica przechowujaca id watkow

    for (int i = 0; i < thread_num; i++) // tworzenie watkow
    {
        int arg = i + 1;
        pthread_t id = create_pt(thread_callback, (void*)&arg);
        threads[i] = id;
        printf("Utworzono wątek o nr '%d' i identyfikatorze: '%ld' \n", arg, id);
        usleep(200); // naprawienie buga, przekazywało ten sam argument do wszystkich callbackow
    }

    gotoxy(0, thread_num + 6); // start komunikatow wzajmengo wykluczania

    for (int i = 0; i < thread_num; i++) // laczenie watkow
    {
        join_pt(threads[i]);
    }

    gotoxy(0, 2 * (thread_num + 4));    // koncowe komunikaty
    

    // sprawdzanie poprawnosci 
    if (section_num * thread_num != global_counter) {
        printf("Wyniki się nie zgadzają! Coś poszło nie tak!\n");
    } else {
        printf("Wyniki są takie same! Wszystko się zgadza!\n");
    }
    exit(EXIT_SUCCESS);
}
