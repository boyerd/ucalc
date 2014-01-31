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
    int code = (strtol(buffer.c_str(),NULL,0) >> SHIFT) & 0x0000FFFF;
    int data = (strtol(buffer.c_str(),NULL,0)) & 0x0000FFFF;
    std::cout << "Factory is creating a (" << code << "," << data << ") object.\n";
    switch(code) {
        case 0:
            return new(std::nothrow) nop(buffer);
            break;
        case 1:
            return new(std::nothrow) jump(buffer,(label*)data);
            break;
        case 2:
            return new(std::nothrow) jz(buffer);
            break;
        case 3:
            return new(std::nothrow) add(buffer,data);
            break;
        case 4:
            return new(std::nothrow) addi(buffer,data);
            break;
        case 5:
            return new(std::nothrow) ldli(buffer,data);
            break;
        case 6:
            return new(std::nothrow) ldhi(buffer,data);
            break;
        case 7:
            return new(std::nothrow) st(buffer,data);
            break;
        case 8:
            return new(std::nothrow) ld(buffer,data);
            break;
        case 9:
            return new(std::nothrow) sub(buffer,data);
            break;
        case 10:
            return new(std::nothrow) subi(buffer,data);
            break;
        case 11:
            return new(std::nothrow) logor(buffer,data);
            break;
        case 12:
            return new(std::nothrow) logori(buffer,data);
            break;
        case 13:
            return new(std::nothrow) logxor(buffer,data);
            break;
        case 14:
            return new(std::nothrow) logxori(buffer,data);
            break;
        case 15:
            return new(std::nothrow) logand(buffer,data);
            break;
        case 16:
            return new(std::nothrow) logandi(buffer,data);
            break;
        case 17:
            return new(std::nothrow) lognot(buffer);
            break;
        default:
            return new(std::nothrow) nop(buffer);
            break;
    }            
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
        delete op;

    }

    std::cout << "Final A: " << proc->a << std::endl;
    std::cout << "Final PC: " << proc->pc << std::endl;
    std::cout << "Memory:\n" << std::endl;

    for (int i = 0; i < proc->sz_data(); i++) {
        std::cout << "0x" << std::hex << i << "\t0x" << proc->rd_data(i) << std::endl;
    }

    return 0;
}
              
