# Aby uruchomić programy na trzy sposoby należy użyć komend:
# 	make run-cw7S
# 	make run-cw7D1
# 	make run-cw7D2


CC = gcc
CFLAGS = -pedantic -Wall -std=gnu99 

NAME0 = main
NAME1 = producent
NAME2 = konsument
SEM_LIB_NAME = semLib
MEM_LIB_NAME = memLib

LIB_NAME = lib
#biblioteka statyczna
LIB_STAT = $(LIB_NAME).a
#biblioteka dzielona
LIB_OUT_NAME = out
LIB_SHAR = $(LIB_OUT_NAME).so
LIB_DIR = lib
LIB_OUT_DIR = myLib


$(SEM_LIB_NAME): $(SEM_LIB_NAME).o
$(MEM_LIB_NAME): $(MEM_LIB_NAME).o

#tworzenie biblioteki statycznej
$(LIB_STAT): ./$(LIB_DIR)/$(SEM_LIB_NAME).o ./$(LIB_DIR)/$(MEM_LIB_NAME).o
	@ar rsv $@ $^
	@mkdir -p $(LIB_OUT_DIR)
	@mv $(LIB_STAT) $(LIB_OUT_DIR)

#tworzenie biblioteki dzielonej
lib$(LIB_SHAR): ./$(LIB_DIR)/$(SEM_LIB_NAME).o ./$(LIB_DIR)/$(MEM_LIB_NAME).o
	@$(CC) -shared -o $@ $(CFLAGS) ./$(LIB_DIR)/$(SEM_LIB_NAME).o ./$(LIB_DIR)/$(MEM_LIB_NAME).o
	@mkdir -p $(LIB_OUT_DIR)
	@mv lib$(LIB_SHAR) $(LIB_OUT_DIR)

SHARED_PREF = S
DYNAMIC_PREF_1 = D1
DYNAMIC_PREF_2 = D2


#tworzenie plikow z biblioteka statyczna
$(NAME0)$(SHARED_PREF): $(NAME0).o 
	$(CC) $(CFLAGS) -o $(NAME0).x ./$(NAME0).o ./$(LIB_OUT_DIR)/$(LIB_STAT)
$(NAME1)$(SHARED_PREF): $(NAME1).o 
	$(CC) $(CFLAGS) -o $(NAME1).x ./$(NAME1).o ./$(LIB_OUT_DIR)/$(LIB_STAT)
$(NAME2)$(SHARED_PREF): $(NAME2).o
	$(CC) $(CFLAGS) -o $(NAME2).x ./$(NAME2).o ./$(LIB_OUT_DIR)/$(LIB_STAT)

#tworzenie plikow z biblioteka dzielona 1
$(NAME0)$(DYNAMIC_PREF_1): $(NAME0).o 
	$(CC) $(CFLAGS) -o $(NAME0).x ./$(NAME0).o -L$(LIB_OUT_DIR) -l$(LIB_OUT_NAME) -Wl,-R $(LIB_OUT_DIR) 
$(NAME1)$(DYNAMIC_PREF_1): $(NAME1).o 
	$(CC) $(CFLAGS) -o $(NAME1).x ./$(NAME1).o -L$(LIB_OUT_DIR) -l$(LIB_OUT_NAME) -Wl,-R $(LIB_OUT_DIR) 
$(NAME2)$(DYNAMIC_PREF_1): $(NAME2).o
	$(CC) $(CFLAGS) -o $(NAME2).x ./$(NAME2).o -L$(LIB_OUT_DIR) -l$(LIB_OUT_NAME) -Wl,-R $(LIB_OUT_DIR)

#tworzenie plikow z biblioteka dzielona 2
$(NAME0)$(DYNAMIC_PREF_2): $(NAME0).o 
	$(CC) $(CFLAGS) -o $(NAME0).x ./$(NAME0).o -L$(LIB_OUT_DIR) -l$(LIB_OUT_NAME) 
$(NAME1)$(DYNAMIC_PREF_2): $(NAME1).o 
	$(CC) $(CFLAGS) -o $(NAME1).x ./$(NAME1).o -L$(LIB_OUT_DIR) -l$(LIB_OUT_NAME) 
$(NAME2)$(DYNAMIC_PREF_2): $(NAME2).o
	$(CC) $(CFLAGS) -o $(NAME2).x ./$(NAME2).o -L$(LIB_OUT_DIR) -l$(LIB_OUT_NAME) 


.PHONY: all$(SHARED_PREF)
all$(SHARED_PREF): $(NAME0)$(SHARED_PREF) $(NAME1)$(SHARED_PREF) $(NAME2)$(SHARED_PREF)
 
.PHONY: all$(DYNAMIC_PREF_1)
all$(DYNAMIC_PREF_1): $(NAME0)$(DYNAMIC_PREF_1) $(NAME1)$(DYNAMIC_PREF_1) $(NAME2)$(DYNAMIC_PREF_1)

.PHONY: all$(DYNAMIC_PREF_2)
all$(DYNAMIC_PREF_2): $(NAME0)$(DYNAMIC_PREF_2) $(NAME1)$(DYNAMIC_PREF_2) $(NAME2)$(DYNAMIC_PREF_2)
  

.PHONY: run-cw7$(SHARED_PREF)
run-cw7$(SHARED_PREF): 
	make clean
	make lib.a
	make all$(SHARED_PREF)
	./$(NAME0).x "./$(NAME1).x" "./$(NAME2).x" "./zrodlo.txt"  "./wynik.txt"
	diff -s ./wynik.txt ./zrodlo.txt

.PHONY: run-cw7$(DYNAMIC_PREF_1)
run-cw7$(DYNAMIC_PREF_1):
	make clean 
	make libout.so
	make all$(DYNAMIC_PREF_1)
	./$(NAME0).x "./$(NAME1).x" "./$(NAME2).x" "./zrodlo.txt"  "./wynik.txt"
	diff -s ./wynik.txt ./zrodlo.txt

.PHONY: run-cw7$(DYNAMIC_PREF_2)
run-cw7$(DYNAMIC_PREF_2): 
	make clean
	make libout.so
	make all$(DYNAMIC_PREF_2)
	@(export LD_LIBRARY_PATH=${LIB_OUT_DIR}:${LD_LIBRARY_PATH}; ./$(NAME0).x "./$(NAME1).x" "./$(NAME2).x" "./zrodlo.txt"  "./wynik.txt")
	diff -s ./wynik.txt ./zrodlo.txt

.PHONY: clean
clean:
	rm -f *.o *.x
	rm lib/*.o -f
	rm myLib -r -f
