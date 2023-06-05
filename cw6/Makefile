CC = gcc
CFLAGS = -pedantic -Wall -std=c99 

NAME1 = powielacz
NAME2 = czytelnik
LIB_NAME = lib

$(NAME1): $(NAME1).o 
	$(CC) $(CFLAGS) -o $(NAME1).x ./$(NAME1).o ./lib/$(LIB_NAME).o

$(NAME2): $(NAME2).o
	$(CC) $(CFLAGS) -o $(NAME2).x ./$(NAME2).o ./lib/$(LIB_NAME).o

.PHONY: all
all: $(NAME1) $(NAME2)

.PHONY: run-cw6
run-cw6: 
	make all
	./$(NAME1).x "./$(NAME2).x" 3 2 3 2
# ./$(NAME1).x (nazwa czytelnika) (liczba procesów) (liczba sekcji krytycznych 1) (liczba sekcji krytycznych 2) ...

.PHONY: clean
clean:
	rm *.o *.x
