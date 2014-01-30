
.PHONY: clean

all: assembler


assembler: main.cpp instruction.cpp
	g++ -Wall main.cpp listing.cpp util.cpp -o assembler

clean:
	-rm -fr assembler
