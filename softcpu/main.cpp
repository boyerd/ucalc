#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>

#include "system_state.h"
#include "label.h"
#include "symbol.h"
#include "instruction.h"

void print_usage(std::string pname) {
    std::cout << "Usage: " << pname << " [input file]\n";
}

instruction* instruction_factory(std::string buffer) {
    return new(std::nothrow) nop(buffer);
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

    // declare our system state
    system_state* proc;
    proc = new(std::nothrow) system_state;

    if(!proc) {
        std::cout << "Error allocating system state.\n";
        return -1;
    }

    proc->a = 0;
    proc->pc = 0;

    std::string buffer;
    int data = 0;
    instruction* op;

    while(std::getline(input,buffer)) {
        
        op = instruction_factory(buffer);
        if (!op) {
            std::cout << "Error reading line " << cntr << ".  Instruction not recognized.\n";
            std::cout << "Line " << cntr << ": " << buffer << std::endl;
            return -1;
        }
        data = strtol(buffer.c_str(),NULL,0) & 0x0000FFFF;
        op->run(proc,data);
        proc->pc += 1;
        delete op;

    }

    std::cout << "Final A: " << proc->a << std::endl;
    std::cout << "Final PC: " << proc->pc << std::endl;

    return 0;
}
              
