BIN=assembler
SRC=main.cpp listing.cpp util.cpp
.PHONY: clean

all: $(BIN)


$(BIN): $(SRC)	 
	g++ -Wall -I ../include/ $(SRC) -o $(BIN)

clean:
	-rm -fr $(BIN) 
