CC = gcc
CFLAGS = -pedantic -Wall -std=c99 

NAME1 = cw2
NAME2 = printOutInfo


$(NAME1): $(NAME1).o
	$(CC) $(CFLAGS) $(NAME1).o -o $(NAME1).x
	$(CC) $(CFLAGS) $(NAME2).c -o $(NAME2).x

$(NAME2): $(NAME2).o
	$(CC) $(CFLAGS) $(NAME2).o -o $(NAME2).x


.PHONY: all
all: $(NAME1) $(NAME2)

.PHONY: run-$(NAME1)
run-$(NAME1): 
	./$(NAME1).x "./$(NAME2).x"

.PHONY: clean
clean:
	rm *.o *.x 
