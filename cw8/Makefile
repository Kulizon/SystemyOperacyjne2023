CC = gcc
CFLAGS = -pedantic -Wall -std=c99 -lrt

NAME1 = klient
NAME2 = serwer
LIB_NAME = lib

$(NAME1): $(NAME1).o 
	$(CC) $(CFLAGS) -o $(NAME1).x ./$(NAME1).o ./lib/$(LIB_NAME).o

$(NAME2): $(NAME2).o
	$(CC) $(CFLAGS) -o $(NAME2).x ./$(NAME2).o ./lib/$(LIB_NAME).o

$(LIB_NAME): ./lib/$(LIB_NAME).o

.PHONY: all
all: $(LIB_NAME) $(NAME1) $(NAME2)

.PHONY: run-cw8
run-cw8: 
	make all
	xterm -hold -title SERWER -bg red -fg black -e ./$(NAME2).x & 
	xterm -hold -title KLIENT1 -bg green -fg black -e ./$(NAME1).x &
	xterm -hold -title KLIENT2 -bg green -fg black -e ./$(NAME1).x &

.PHONY: clean
clean:
	rm *.o *.x