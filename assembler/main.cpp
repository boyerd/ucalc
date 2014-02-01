#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

#include "verb.h"
#include "symbol.h"
#include "label.h"
#include "instruction.h"
#include "listing.h"

void print_usage(std::string pname) {
    std::cout << "Usage: " << pname << " [input file]\n";
}

int main(int argc, char *argv[]) {

    std::ifstream input;
    std::ofstream output;
    int cntr = 0;

    setloglevel(0);

    if (argc < 2) {
        print_usage(argv[0]);
        return -1;
    }

    //open input file
    input.open(argv[1], std::ios::in);

    if (!input.is_open()) {
        log(ERROR) << "Error opening input source " << argv[1] << ".\n";
        return -1;
    }

    //declare our input buffers
    listing program;
    std::string buffer;

    //read input, parsing each string and then passing it into the instruction factory
    cntr = 0;
    while(std::getline(input,buffer)) {

        ++cntr;
        if (program.factory(buffer) != 0) {
            log(ERROR) << "Error reading line " << cntr << ".  Instruction not recognized.\n";
            log(ERROR) << "Line " << cntr << ": " << buffer << std::endl;
            return -1;
        }

    }

    //print out all instructions;
    cntr = 0;
    program.print();
    
    return 0;

}

