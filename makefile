CC = g++ -std=c++0x  #g++ -std=c++11
DEBUG = -g
CFLAGS = -Wall -c -O3 $(DEBUG)
LFLAGS = -Wall -O3 $(DEBUG)
PTH = .
SRC = $(PTH)/src
INC = $(PTH)/lib
BIN = $(PTH)/bin

.all: clean real random



$(BIN)/check_src: $(SRC)/main.cpp $(SRC)/simp.cpp $(SRC)/improv.cpp $(SRC)/kpath.cpp $(SRC)/k_lev.cpp 

$(BIN)/check_lib: $(INC)/levelAnc.cpp $(INC)/tree.cpp $(INC)/verifydfs.cpp



$(BIN)/main_varn: $(BIN)/check_src $(BIN)/check_lib
	$(CC) $(LFLAGS) -D VARN $(SRC)/main.cpp -o \
				$(BIN)/main_VARN

$(BIN)/main_varm: $(BIN)/check_src $(BIN)/check_lib
	$(CC) $(LFLAGS) -D VARM $(SRC)/main.cpp -o \
				$(BIN)/main_VARM

$(BIN)/main_vark: $(BIN)/check_src $(BIN)/check_lib
	$(CC) $(LFLAGS) -D VARK $(SRC)/main.cpp -o \
				$(BIN)/main_VARK




$(BIN)/main_real: $(BIN)/check_src $(BIN)/check_lib
	$(CC) $(LFLAGS) -D REAL $(SRC)/main.cpp -o \
				$(BIN)/main_REAL

$(BIN)/main_random: $(BIN)/main_varn $(BIN)/main_varm $(BIN)/main_vark




clean:
	rm bin/*

real: $(BIN)/main_real

random: $(BIN)/main_random