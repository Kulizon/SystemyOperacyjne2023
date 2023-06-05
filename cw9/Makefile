CC = gcc
CFLAGS = -pedantic -Wall -std=c99 -lpthread

NAME1 = main
LIB_NAME = lib

$(NAME1): $(NAME1).o 
	$(CC) $(CFLAGS) -o $(NAME1).x ./$(NAME1).o ./lib/$(LIB_NAME).o

$(LIB_NAME): ./lib/$(LIB_NAME).o

.PHONY: all
all: $(LIB_NAME) $(NAME1) $(NAME2)

.PHONY: run-cw9
run-cw9: 
	make all
	./$(NAME1).x 3 3

.PHONY: clean
clean:
	rm *.o *.x