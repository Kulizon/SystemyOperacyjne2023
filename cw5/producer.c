#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define CHUNK 7

int main(int argc, char *argv[]) {
    char *inFilePath = argv[1];

    int pipe = open(argv[2], O_WRONLY, 0644);
    if (pipe == -1) {
        perror ("ERROR OPENING PIPE PRODUCER");
	    exit (EXIT_FAILURE);
    }

    // Na początku każdy z procesów powinien zamknąć nieużywaną część potoku.
    // if (close (pipe) == -1) { 
	// 	perror ("ERROR CLOSING PIPE");
	// 	exit (EXIT_FAILURE);
	// }

    size_t source = open(inFilePath, O_RDONLY);
    if (source == -1) {
        perror("OPENING IN/OUT FILES ERROR\n");
        exit(EXIT_FAILURE);
    }

    int producerBytesRead, pipeBytesWritten;
    char producerBuffer[CHUNK];
    char producerReadText[1024];

    while ((producerBytesRead = read(source, producerBuffer, CHUNK))) {
            printf ("Odczytano %d bajtow z pliku.\n", producerBytesRead);

            if(producerBytesRead == -1) {
                perror("READ ERROR PRODUCER\n");
                exit(EXIT_FAILURE);
            }
            
            memset(producerReadText, 0, sizeof(producerReadText));
			snprintf (producerReadText, sizeof("Dane wyczytane z pliku przez producenta: \n") + sizeof(producerBuffer), "Dane wyczytane z pliku przez producenta: \n%s\n", producerBuffer);
            write (STDOUT_FILENO, producerReadText, strlen(producerReadText));
            
            pipeBytesWritten = write(pipe, producerBuffer, producerBytesRead);

            if(pipeBytesWritten == -1) {
                perror("WRITE ERROR PRODUCER\n");
                exit(EXIT_FAILURE);
            }

            printf ("\nPrzeslano %d bajtow do potoku.\n", pipeBytesWritten);
            sleep(rand() % 3 + 1);
    }

    if (close (pipe) == -1 || close(source) == -1) { 
				perror ("ERROR CLOSING PRODUCER\n");
				exit (EXIT_FAILURE);
		}

    printf ("\n========= Przesylanie do potoku zakonczone! =========\n\n");

    // //
    //
    // Todo + obsługa błędów - write i read zwracaja chyba -1 na bledzie
    // 
    // // 

    // Po zakończeniu przesyłania danych, oba procesy powinny zamknąć drugą część potoku oraz otwarty plik.

    exit (EXIT_SUCCESS);
}