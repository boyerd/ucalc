CXX=g++
CFLAGS=-c -Wall
LDFLAGS=
INCL=../include

BIN=softcpu
SRC=main.cpp 

OBJS=$(SRC:.cpp=.o)

.PHONY: clean

all: $(BIN)

$(BIN): $(OBJS)	 
	$(CXX) $(LDFLAGS) -I $(INCL) $(SRC) -o $(BIN)

.cpp.o:
	$(CXX) $(CFLAGS) -I $(INCL) $< -o $@

clean:
	-rm -fr $(BIN)  *.o
