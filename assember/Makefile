
.PHONY: clean

all: assembler


assembler: main.cpp listing.cpp util.cpp
	g++ -Wall -I ../include/ main.cpp listing.cpp util.cpp -o assembler

clean:
	-rm -fr assembler
