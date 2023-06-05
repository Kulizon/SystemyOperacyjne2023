CC = gcc
CFLAGS = -pedantic -Wall -std=c99 

NAME = cw4
IN_NAME = dane
OUT_NAME = wynik

$(NAME): $(NAME).o
	$(CC) $(CFLAGS) $(NAME).o -o $(NAME).x

.PHONY: all
all: $(NAME)

.PHONY: run-$(NAME)
run-$(NAME): 
	./$(NAME).x ./$(IN_NAME).txt ./$(OUT_NAME).txt 
	diff -s ./$(IN_NAME).txt ./$(OUT_NAME).txt


.PHONY: clean
clean:
	rm *.o *.x 
