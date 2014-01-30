#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#include "symbol.h"
#include "label.h"
#include "listing.h"
#include "instruction.h"
#include "util.h"

listing::listing(void) {
    opstbl = new std::vector<instruction*>;
    symtbl = new std::vector<symbol*>;
    lbltbl = new std::vector<label*>;
}

listing::~listing(void) {
    delete opstbl;
    delete symtbl;
    delete lbltbl;
}

int listing::factory(std::string input) {

    std::string ins;
    //trim off leading whitespace
    input = trim(input);
    //return the instruction mnemonic
    ins = cmd(input);

    std::cout << "Instruction factory processing '" << input << "'" << std::endl;

    // detected a label
    if (ins.at(ins.length()-1) == ':') {
        std::cout << "Found label '" << ins << "'\n";
        return 0;
    }

    // detected a symbol

    // must be an instruction?  parse as such
    if (ins == "nop") {
        opstbl->insert(opstbl->end(),new nop(input)); 
    } else if (ins == "clr") {
        opstbl->insert(opstbl->end(),new clr(input)); 
    } else if (ins == "jz") {
        opstbl->insert(opstbl->end(),new jz(input)); 
    } else if (ins == "add") {
        opstbl->insert(opstbl->end(),new add(input, 0)); 
    } else if (ins == "addi") {
        opstbl->insert(opstbl->end(),new addi(input)); 
    } else if (ins == "ldli") {
        opstbl->insert(opstbl->end(),new ldli(input));
    } else if (ins == "ldhi") {
        opstbl->insert(opstbl->end(),new ldhi(input));
    } else if (ins[0] == '$') {
        opstbl->insert(opstbl->end(),new ref(input, 0));
    }
    else
        return -1;
    
    return 0;
}

void listing::print(void) {
    int cntr = 0;
    for (std::vector<instruction*>::iterator it = opstbl->begin(); it != opstbl->end(); ++it) {
        std::cout << cntr++ << ":\t0x" << std::setfill('0') << std::setw(8) << std::hex << (*it)->ins();
        std::cout << "\t\t(" <<  (*it)->mnemonic << ")\n";
    }


}

