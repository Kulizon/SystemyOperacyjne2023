CC = gcc
CFLAGS = -pedantic -Wall -std=c99 

NAME1 = cw3a
NAME2 = cw3b
NAME3 = cw3c
NAME4 = helper

$(NAME1): $(NAME1).o
	$(CC) $(CFLAGS) $(NAME1).o -o $(NAME1).x

$(NAME2): $(NAME2).o
	$(CC) $(CFLAGS) $(NAME2).o -o $(NAME2).x
	make $(NAME1)

$(NAME4): $(NAME4).o
	$(CC) $(CFLAGS) $(NAME4).o -o $(NAME4).x

$(NAME3): $(NAME3).o
	$(CC) $(CFLAGS) $(NAME3).o -o $(NAME3).x
	make $(NAME1)
	make $(NAME4)


.PHONY: all
all: $(NAME1) $(NAME2) $(NAME3) $(NAME4)

.PHONY: run-$(NAME1)
run-$(NAME1): 
	./$(NAME1).x 3 17

.PHONY: run-$(NAME2)
run-$(NAME2): 
	./$(NAME2).x 3 17 ./$(NAME1).x

.PHONY: run-$(NAME3)
run-$(NAME3): 
	./$(NAME3).x 3 17 ./$(NAME1).x ./$(NAME4).x

.PHONY: clean
clean:
	rm *.o *.x 
