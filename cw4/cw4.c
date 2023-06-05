#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

#define CHUNK 6
#define CHUNK2 4

int main(int argc, char *argv[]) {
    char *inFilePath = argv[1];
    char *outFilePath = argv[2];

    if(argc != 3) {
        printf("TOO LITTLE ARGUMENTS \n");
        exit(EXIT_FAILURE);
    }

    int despipe[2];
    if(pipe(despipe) == -1) {
        perror("PIPE ERROR\n");
        exit(EXIT_FAILURE);
    }
    
    size_t dest = open(outFilePath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    size_t source = open(inFilePath, O_RDONLY);

    if (source == -1 || dest == -1) {
        perror("OPENING IN/OUT FILES ERROR\n");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    switch (pid)
    {
    case 0: ;
        int consumerBytesWritten, pipeBytesRead;
        char consumerBuffer[CHUNK];

        if (close (despipe[1]) == -1) { 
				perror ("ERROR CLOSING PIPE 1");
				exit (EXIT_FAILURE);
		}

        char consumerReadText[1038];

        while ((pipeBytesRead = read(despipe[0], consumerBuffer, CHUNK2))) {
            printf ("Odczytano %d bajtow z potoku.\n", pipeBytesRead);

            if(pipeBytesRead == -1) {
                perror("READ ERROR CONSUMER\n");
                exit(EXIT_FAILURE);
            }

			sprintf (consumerReadText, "Dane wyczytane z potoku przez konsumenta: \n%s\n", consumerBuffer);
            write (STDOUT_FILENO, consumerReadText, strlen(consumerReadText));
            consumerBytesWritten = write(dest, consumerBuffer, pipeBytesRead);

            if (consumerBytesWritten == -1) {
                perror("WRITE ERROR CONSUMER\n");
                exit(EXIT_FAILURE);
            }

            printf ("Zapisano %d bajtow do pliku\n", pipeBytesRead);
            sleep(rand() % 3 + 1);
        }

        if (close (despipe[0]) == -1 || close(dest) == -1) {
			perror ("ERROR CLOSING CONSUMER\n");
			exit (EXIT_FAILURE);
		}

        break;
    case -1: ;
        perror("FORK ERROR\n");
        exit(EXIT_FAILURE);
        break;
    
    default: ;
        int producerBytesRead, pipeBytesWritten;
        char producerBuffer[CHUNK];

        if (close (despipe[0]) == -1) { 
				perror ("ERROR CLOSING PIPE 2");
				exit (EXIT_FAILURE);
		}

        char producerReadText[1024];

        while ((producerBytesRead = read(source, producerBuffer, CHUNK))) {
            printf ("Odczytano %d bajtow z pliku.\n", producerBytesRead);

            if(producerBytesRead == -1) {
                perror("READ ERROR PRODUCER\n");
                exit(EXIT_FAILURE);
            }
            
			sprintf (producerReadText, "Dane wyczytane z pliku przez producenta: \n%s\n", producerBuffer);
            write (STDOUT_FILENO, producerReadText, strlen(producerReadText));

            pipeBytesWritten = write(despipe[1], producerBuffer, producerBytesRead);

            if(pipeBytesWritten == -1) {
                perror("WRITE ERROR PRODUCER\n");
                exit(EXIT_FAILURE);
            }

            printf ("Przeslano %d bajtow do potoku.\n", pipeBytesWritten);
            sleep(rand() % 3 + 1);
            
        }

        if (close (despipe[1]) == -1 || close(source) == -1) { 
				perror ("ERROR CLOSING PRODUCER\n");
				exit (EXIT_FAILURE);
		}
        if (wait (NULL) == -1) {
				perror ("WAIT ERROR");
				exit (EXIT_FAILURE);
		}

        break;
    }

    exit (EXIT_SUCCESS);
}