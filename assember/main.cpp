#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

#include "symboltable.h"
#include "labeltable.h"
#include "instruction.h"
#include "program.h"

void print_usage(std::string pname) {
    std::cout << "Usage: " << pname << " [input file]\n";
}


int main(int argc, char *argv[]) {

    std::ifstream input;
    std::ofstream output;
    int cntr = 0;

    if (argc < 2) {
        print_usage(argv[0]);
        return -1;
    }

    //open input file
    input.open(argv[1], std::ios::in);

    if (!input.is_open()) {
        std::cout << "Error opening input source " << argv[1] << ".\n";
        return -1;
    }

    //declare our input buffers
    std::vector<instruction*> program;
    std::string buffer;

    //read input, parsing each string and then passing it into the instruction factory
    cntr = 0;
    while(std::getline(input,buffer)) {

        ++cntr;
        if (instruction_factory(buffer,program) != 0) {
            std::cout << "Error reading line " << cntr << ".  Instruction not recognized.\n";
            std::cout << "Line " << cntr << ": " << buffer << std::endl;
            return -1;
        }

    }

    //print out all instructions;
    cntr = 0;
    for (std::vector<instruction*>::iterator it = program.begin(); it != program.end(); ++it) {
        std::cout << cntr++ << ":\t0x" << std::setfill('0') << std::setw(8) << std::hex << (*it)->ins();
        std::cout << "\t\t(" <<  (*it)->mnemonic << ")\n";
    }

    instruction_optimize(program);

    
    return 0;

}
