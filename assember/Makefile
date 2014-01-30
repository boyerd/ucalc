
.PHONY: clean

all: assembler


assembler: main.cpp instruction.cpp
	g++ -Wall main.cpp symboltable.cpp instruction.cpp -o assembler

clean:
	-rm -fr assembler
