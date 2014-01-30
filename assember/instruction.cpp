#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

#include "symboltable.h"
#include "instruction.h"

symboltable symtbl;

void trim(std::string& s)
{
   size_t p = s.find_first_not_of(" \t");
   s.erase(0, p);

   p = s.find_last_not_of(" \t");
   if (std::string::npos != p)
      s.erase(p+1);
}

std::string cmd(const std::string& s) {
    std::string rval;
    size_t p = s.find_first_of(" \t\n");
    rval = s.substr(0,p);
    return rval;
}

std::string argify(const std::string& s) {
    std::string rval;
    size_t p = s.find_first_of(" \t\n");
    rval = s.substr(p);
    trim(rval);
    //remove trailing space as well
    p = rval.find_first_of(" \t\n");
    rval = rval.substr(0,p);
    return rval;
}

int instruction_factory(std::string input, std::vector<instruction*>& insbuf) {
    std::string ins;
    //trim off leading whitespace
    trim(input);
    //return the instruction mnemonic
    ins = cmd(input);

    std::cout << "Instruction factory processing '" << input << "'" << std::endl;

    if (ins.at(ins.length()-1) == ':')
        std::cout << "Found label '" << ins << "'\n";
    else if (ins == "nop")
        insbuf.insert(insbuf.end(),new nop(input)); 
    else if (ins == "clr")
        insbuf.insert(insbuf.end(),new clr(input)); 
    else if (ins == "jz")
        insbuf.insert(insbuf.end(),new jz(input)); 
    else if (ins == "add")
        insbuf.insert(insbuf.end(),new add(input)); 
    else if (ins == "addi")
        insbuf.insert(insbuf.end(),new addi(input)); 
    else if (ins == "ldli")
        insbuf.insert(insbuf.end(),new ldli(input));
    else if (ins == "ldhi")
        insbuf.insert(insbuf.end(),new ldhi(input));
    else if (ins[0] == '$') {
        insbuf.insert(insbuf.end(),new ref(input));
        symtbl.add_symbol(ins);
    }
    else
        return -1;
    
    return 0;
}

int instruction_optimize(std::vector<instruction*>& program) {
    symtbl.print_symbols();
    symtbl.merge_symbols(program);
    symtbl.print_symbols();
    return 0;
}
