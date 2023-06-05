CC = gcc
CFLAGS = -pedantic -Wall -std=c99 

NAME1 = cw5a
NAME2 = cw5b
IN_NAME = dane
OUT_NAME = wynik
PRODUCER_NAME = producer
CONSUMER_NAME = consumer

# ./cw5a.x "./dane.txt" "./wynik.txt" "./reader.x" "./writter.x"

$(NAME1): $(NAME1).o
	$(CC) $(CFLAGS) $(NAME1).o -o $(NAME1).x
	make $(PRODUCER_NAME)
	make $(CONSUMER_NAME)

$(NAME2): $(NAME1).o
	$(CC) $(CFLAGS) $(NAME1).o -o $(NAME1).x
	make $(PRODUCER_NAME)
	make $(CONSUMER_NAME)

$(PRODUCER_NAME): $(PRODUCER_NAME).o
	$(CC) $(CFLAGS) $(PRODUCER_NAME).o -o $(PRODUCER_NAME).x

$(CONSUMER_NAME): $(CONSUMER_NAME).o
	$(CC) $(CFLAGS) $(CONSUMER_NAME).o -o $(CONSUMER_NAME).x

.PHONY: all
all: $(NAME1) $(CONSUMER_NAME) $(PRODUCER_NAME)

.PHONY: run-$(NAME1)
run-$(NAME1): 
	./$(NAME1).x "./$(IN_NAME).txt" "./$(OUT_NAME).txt" "./$(PRODUCER_NAME).x" "./$(CONSUMER_NAME).x" 
	diff -s ./$(IN_NAME).txt ./$(OUT_NAME).txt

# -hold - flaga, aby xterm nie zamykał się automatycznie
.PHONY: run-$(NAME2)
run-$(NAME2): 
	[ -p moj_fifo ] || mkfifo moj_fifo
	
	xterm -title PRODUCENT -e ./$(PRODUCER_NAME).x dane.txt moj_fifo &
	xterm -title KONSUMENT -e ./$(CONSUMER_NAME).x  wynik.txt moj_fifo
	rm moj_fifo
	diff -s ./$(IN_NAME).txt ./$(OUT_NAME).txt


.PHONY: clean
clean:
	rm *.o *.x 
