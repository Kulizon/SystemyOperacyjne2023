#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define CHUNK 5

int main(int argc, char *argv[]) {
    char *outFilePath = argv[1];

    int pipe = open(argv[2], O_RDONLY, 0644);
    if (pipe == -1) {
        perror ("ERROR OPENING PIPE CONSUMER");
	    exit (EXIT_FAILURE);
    }

    // Na początku każdy z procesów powinien zamknąć nieużywaną część potoku.
    //
    //
    //

    size_t dest = open(outFilePath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest == -1) {
        perror("OPENING IN/OUT FILES ERROR\n");
        exit(EXIT_FAILURE);
    }

    int consumerBytesWritten, pipeBytesRead;
    char consumerBuffer[CHUNK];
    char consumerReadText[1038];

    while ((pipeBytesRead = read(pipe, consumerBuffer, CHUNK))) {
        printf ("Odczytano %d bajtow z potoku.\n", pipeBytesRead);

        if(pipeBytesRead == -1) {
            perror("READ ERROR CONSUMER\n");
            exit(EXIT_FAILURE);
        }

        if (pipeBytesRead > 0) {
            memset(consumerReadText, 0, sizeof(consumerReadText));
            snprintf (consumerReadText, sizeof("Dane wyczytane z potoku przez konsumenta: \n") + sizeof(consumerBuffer),  "Dane wyczytane z potoku przez konsumenta: \n%s\n", consumerBuffer);
            write (STDOUT_FILENO, consumerReadText, strlen(consumerReadText));
        } 
        
        consumerBytesWritten = write(dest, consumerBuffer, pipeBytesRead);

        if (consumerBytesWritten == -1) {
            perror("WRITE ERROR CONSUMER\n");
            exit(EXIT_FAILURE);
        }

        printf ("\nZapisano %d bajtow do pliku\n", pipeBytesRead);
        sleep(rand() % 3 + 1);
        }

    if (close (pipe) == -1 || close(dest) == -1) {
		perror ("ERROR CLOSING CONSUMER\n");
		exit (EXIT_FAILURE);
	}

    printf ("\n========= Zapisywanie do pliku zakonczone! =========\n\n");


    // //
    //
    // Todo + obsługa błędów
    // 
    // // 

    // Po zakończeniu przesyłania danych, oba procesy powinny zamknąć drugą część potoku oraz otwarty plik.


    exit (EXIT_SUCCESS);
    
}
