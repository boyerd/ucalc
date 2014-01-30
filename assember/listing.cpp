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
    std::string arg;

    // trim off leading whitespace
    input = trim(input);
    // return the instruction mnemonic
    ins = cmd(input);

    std::cout << "Instruction factory processing '" << input << "'" << std::endl;

    // detected a label
    if (ins.at(ins.length()-1) == ':') {
        std::cout << "Found label '" << ins << "'\n";
        lbltbl->insert(lbltbl->end(),new label(ins,opstbl->size()));
        return 0;
    }

    // if not a label, we need to extract the argument
    arg = trim(input.substr(ins.length()));

    // detected a symbol definition
    if (ins[0] == '$') {
        std::cout << "Found symbol '" << ins << "' with value '" << arg << "'\n";
        symtbl->insert(symtbl->end(),new symbol(ins));
        return 0;
    }

    // must be an instruction?  parse as such
    if (ins == "nop") {
        opstbl->insert(opstbl->end(),new nop(input)); 
    } else if (ins == "clr") {
        opstbl->insert(opstbl->end(),new clr(input)); 
    } else if (ins == "jz") {
        opstbl->insert(opstbl->end(),new jz(input)); 
    } else if (ins == "add") {
        symtbl->insert(symtbl->end(),new symbol(arg));
        opstbl->insert(opstbl->end(),new add(input, 0)); 
    } else if (ins == "addi") {
        opstbl->insert(opstbl->end(),new addi(input)); 
    } else if (ins == "ldli") {
        opstbl->insert(opstbl->end(),new ldli(input));
    } else if (ins == "ldhi") {
        opstbl->insert(opstbl->end(),new ldhi(input));
    }
    else
        return -1;
    
    return 0;
}

void listing::print(void) {

    std::cout << "Instruction table:\n";
    for (std::vector<instruction*>::iterator it = opstbl->begin(); it != opstbl->end(); ++it) {
        std::cout << it - opstbl->begin() << ":\t0x" << std::setfill('0') << std::setw(8) << std::hex << (*it)->ins();
        std::cout << "\t\t(" <<  (*it)->mnemonic << ")\n";
    }

    std::cout << "Symbol table:\n";
    for (std::vector<symbol*>::iterator it = symtbl->begin(); it != symtbl->end(); ++it) {
        std::cout << "0x" << it - symtbl->begin() << "\t\t" << (*it)->name << std::endl;
    }

    std::cout << "Label table:\n";
    for (std::vector<label*>::iterator it = lbltbl->begin(); it != lbltbl->end(); ++it) {
        std::cout << (*it)->name << " 0x" << (*it)->op_id << " (" << opstbl->at((*it)->op_id)->mnemonic << ")" << std::endl; 
    }


}

