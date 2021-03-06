#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <iterator>
#include <stdlib.h>

#include "verb.h"
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
    for (std::vector<instruction*>::iterator it = opstbl->begin(); it != opstbl->end(); ++it) {
        delete (*it);
    }

    for (std::vector<symbol*>::iterator it = symtbl->begin(); it != symtbl->end(); ++it) {
        delete (*it);
    }

    for (std::vector<label*>::iterator it = lbltbl->begin(); it != lbltbl->end(); ++it) {
        delete (*it);
    }

    delete opstbl;
    delete symtbl;
    delete lbltbl;
}

int listing::addsymbol(std::string input) {

    int index = -1;
    for (std::vector<symbol*>::iterator it = symtbl->begin(); it != symtbl->end(); ++it) {
        if ((*it)->name == input) {
            log(DETAIL) << "\tSymbol " << input << " found at ";
            log(DETAIL) << it - symtbl->begin() << std::endl;
//            return it - symtbl->begin();
            return std::distance(symtbl->begin(), it);
        }
    }
    log(DETAIL) << "\tSymbol not found, inserted at position ";
    index = std::distance(symtbl->begin(),
        symtbl->insert(symtbl->end(),new symbol(input)));
    log(DETAIL) << index << std::endl;
    return index;

}

// an op index of -1 indicates that the label is a j target and may
// not exist in the jump table yet.
label* listing::addlabel(std::string input, int op) {

    int index = -1;
    for (std::vector<label*>::iterator it = lbltbl->begin(); it != lbltbl->end(); ++it) {
        if ((*it)->name == input) {
            log(DETAIL) << "\tLabel " << input << " found at ";
            log(DETAIL) << it - lbltbl->begin() << " targeting "<< (*it)->op_id << std::endl;
            if ((*it)->op_id < op) {
                log(DETAIL) << "\tRetargetting to " << op;
                if ((*it)->op_id != -1)
                    log(DETAIL) << " (Note: duplicate label?)"; 
                log(DETAIL) << std::endl;
                (*it)->op_id = op;
            }

            //return std::distance(lbltbl->begin(), it);
            return *it;
        }
    }
    log(DETAIL) << "\tLabel not found, inserted at position ";
    std::vector<label*>::iterator lbl;
    lbl = lbltbl->insert(lbltbl->end(),new label(input,op));
    index = std::distance(lbltbl->begin(),lbl);
    log(DETAIL) << index << " targeting " << op << std::endl;
    return *lbl;

}

int listing::factory(std::string input) {

    std::string ins;
    std::string arg;

    // strip any comments from the input line
    input = rmcomment(input);

    // trim off leading whitespace
    input = trim(input);
    // return the instruction mnemonic
    ins = cmd(input);
    arg = trim(input.substr(ins.length()));

    log(BASIC) << "Instruction factory processing '" << input << "' ";


    if (ins == "") {
        log(BASIC) << " ...failed to recognize an instruction...\n";
        return 0;
    }


    // detected a label
    if (ins.at(ins.length()-1) == ':') {
        log(BASIC) << "\n\tFound label '" << ins << "'\n";
        //lbltbl->insert(lbltbl->end(),new label(ins,opstbl->size()));
        addlabel(ins,opstbl->size());
        return 0;
    }

    // detected a symbol definition
    if (ins[0] == '$') {
        log(BASIC) << "\n\tFound symbol '" << ins << "' with value '" << arg << "'\n";
        // fake the value setting with a pair of load instructions and a store
        opstbl->insert(opstbl->end(),new ldli(input,
                    strtol(arg.c_str(),NULL,0)));
        opstbl->insert(opstbl->end(),new ldhi(input,
                    strtol(arg.c_str(),NULL,0)));
        opstbl->insert(opstbl->end(),new st(input, 
                addsymbol(ins)));
        return 0;
    }

    // must be an instruction?  parse as such
    log(BASIC) << "Ins: '" << ins << "' Arg: '" << arg << "'";
    log(BASIC) << std::endl;

    if (ins == "nop") {
        opstbl->insert(opstbl->end(),new nop(input)); 

    } else if (ins == "clr") { // pseudo instruction
        opstbl->insert(opstbl->end(),new ldli(input,0));
        opstbl->insert(opstbl->end(),new ldhi(input,0));

    } else if (ins == "jz") {
        opstbl->insert(opstbl->end(),new jz(input)); 

    } else if (ins == "jump") {
        opstbl->insert(opstbl->end(),new jump(input,
                    addlabel(arg,-1))); 

    } else if (ins == "add") {
        opstbl->insert(opstbl->end(),new add(input, 
                addsymbol(arg)));

    } else if (ins == "addi") {
        opstbl->insert(opstbl->end(),new addi(input,
                    strtol(arg.c_str(),NULL,0)));

    } else if (ins == "sub") {
        opstbl->insert(opstbl->end(),new sub(input, 
                addsymbol(arg)));

    } else if (ins == "subi") {
        opstbl->insert(opstbl->end(),new subi(input,
                    strtol(arg.c_str(),NULL,0)));

    } else if (ins == "ldli") {
        opstbl->insert(opstbl->end(),new ldli(input,
                    strtol(arg.c_str(),NULL,0)));

    } else if (ins == "ldhi") {
        opstbl->insert(opstbl->end(),new ldhi(input,
                    strtol(arg.c_str(),NULL,0)));

    } else if (ins == "ldi") { // pseudo instruction
        opstbl->insert(opstbl->end(),new ldli(input,
                    strtol(arg.c_str(),NULL,0)));
        opstbl->insert(opstbl->end(),new ldhi(input,
                    strtol(arg.c_str(),NULL,0)));

    } else if (ins == "st") {
        opstbl->insert(opstbl->end(),new st(input, 
                addsymbol(arg)));

    } else if (ins == "ld") {
        opstbl->insert(opstbl->end(),new ld(input, 
                addsymbol(arg)));

    } else if (ins == "or") {
        opstbl->insert(opstbl->end(),new logor(input, 
                addsymbol(arg)));

    } else if (ins == "ori") {
        opstbl->insert(opstbl->end(),new logori(input,
                    strtol(arg.c_str(),NULL,0)));

    } else if (ins == "xor") {
        opstbl->insert(opstbl->end(),new logxor(input, 
                addsymbol(arg)));

    } else if (ins == "xori") {
        opstbl->insert(opstbl->end(),new logxori(input,
                    strtol(arg.c_str(),NULL,0)));

    } else if (ins == "and") {
        opstbl->insert(opstbl->end(),new logand(input, 
                addsymbol(arg)));

    } else if (ins == "andi") {
        opstbl->insert(opstbl->end(),new logandi(input,
                    strtol(arg.c_str(),NULL,0)));

    } else if (ins == "not") {
        opstbl->insert(opstbl->end(),new lognot(input)); 

    } else if (ins == "fin") {
        opstbl->insert(opstbl->end(),new fin(input)); 

    } else {
        return -1;
    }
    
    return 0;
}

void listing::print(void) {

    log(DETAIL) << "\nInstruction table:\n";
    for (std::vector<instruction*>::iterator it = opstbl->begin(); it != opstbl->end(); ++it) {
        log(DETAIL) << it - opstbl->begin() << ":\t0x" << std::setfill('0') << std::setw(8) << std::hex << (*it)->ins();
        log(DETAIL) << "\t\t(" <<  (*it)->mnemonic << ")\n";
    }

    log(DETAIL) << "\nSymbol table:\n";
    for (std::vector<symbol*>::iterator it = symtbl->begin(); it != symtbl->end(); ++it) {
        log(DETAIL) << "0x" << it - symtbl->begin() << "\t\t" << (*it)->name << std::endl;
    }

    log(DETAIL) << "\nLabel table:\n";
    for (std::vector<label*>::iterator it = lbltbl->begin(); it != lbltbl->end(); ++it) {
        log(DETAIL) << (*it)->name << " 0x" << (*it)->op_id << " (" << opstbl->at((*it)->op_id)->mnemonic << ")" << std::endl; 
    }


}

