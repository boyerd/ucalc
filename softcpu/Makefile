BIN=softcpu
SRC=main.cpp 
.PHONY: clean

all: $(BIN)


$(BIN): $(SRC)	 
	g++ -Wall -I ../include/ $(SRC) -o $(BIN)

clean:
	-rm -fr $(BIN) 
