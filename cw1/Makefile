CC = gcc
CFLAGS = -pedantic -Wall -std=c99 

NAME1 = cw1a
NAME2 = cw1b
NAME3 = cw1c
NAME4 = cw1d
NAME5 = cw1e

$(NAME1): $(NAME1).o
	$(CC) $(CFLAGS) $(NAME1).o -o $(NAME1).x
$(NAME2): $(NAME2).o
	$(CC) $(CFLAGS) $(NAME2).o -o $(NAME2).x
$(NAME3): $(NAME3).o
	$(CC) $(CFLAGS) $(NAME3).o -o $(NAME3).x
$(NAME4): $(NAME4).o
	$(CC) $(CFLAGS) $(NAME4).o -o $(NAME4).x
$(NAME5): $(NAME5).o
	$(CC) $(CFLAGS) $(NAME5).o -o $(NAME5).x

%.o: %.c %.h
	$(CO) $(CFLAGS) -c $<

.PHONY: all
all: cw1a cw1b cw1c cw1d cw1e

.PHONY: run-$(NAME1)
run-$(NAME1): 
	make $(NAME1)
	./$(NAME1).x

.PHONY: run-$(NAME2)
run-$(NAME2): 
	make $(NAME2)
	./$(NAME2).x

.PHONY: run-$(NAME3)
run-$(NAME3): 
	make $(NAME3)
	./$(NAME3).x

.PHONY: run-$(NAME4)
run-$(NAME4): 
	make $(NAME4)
	./$(NAME4).x

.PHONY: run-$(NAME5)
run-$(NAME5): 
	make $(NAME5)
	./$(NAME5).x

.PHONY: clean
clean:
	rm *.o *.x 
