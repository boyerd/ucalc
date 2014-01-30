#include <iostream>
#include <vector>

#include "symboltable.h"
#include "instruction.h"

int symboltable::add_symbol(std::string newsym) {
        
    int temp;

    std::cout << "Adding symbol " << newsym << "... ";
    for (std::vector<symbol>::iterator it = table.begin(); it != table.end(); ++it) {
        if ((*it).name == newsym) {
            temp =  it - table.begin();
            std::cout << " symbol " << newsym << " found at " << temp << std::endl;
            return temp;
        }
    }   

    table.push_back(symbol(newsym));
    temp = table.end() - table.begin() - 1;
    std::cout <<  " symbol " << newsym << " inserted at " << temp << std::endl;
    return temp;

}

int symboltable::merge_symbols(std::vector<instruction*>& program) {
    std::cout << "Merging symbols...\n";
    //load first/last use variables
    for (std::vector<instruction*>::iterator it = program.begin(); 
            it != program.end(); ++it) {
        direct* ptr = NULL;
        ptr = dynamic_cast<direct*>(*it);
        if (ptr != NULL) {
            std::cout << "Direct reference instruction found: " << ptr->mnemonic << std::endl;
            if (this->table[ptr->symidx].first_use == -1)
                this->table[ptr->symidx].first_use = it - program.begin();
            if (this->table[ptr->symidx].last_use < it - program.begin()) 
                this->table[ptr->symidx].last_use = it - program.begin();
        } else {
            std::cout << "Non-reference instruction found: " << (*it)->mnemonic << std::endl;
        }
    }
    


    return 0;
}

int symboltable::print_symbols(void) {
    for (std::vector<symbol>::iterator it = table.begin(); it != table.end(); ++it) {
        std::cout << it - table.begin() << " " << (*it).name; 
        if ((*it).first_use != -1)
            std::cout << "\t(" << (*it).first_use;
        else
            std::cout << "\t(??";
        if ((*it).last_use != -1)
            std::cout << "-" << (*it).last_use << ")";
        else
            std::cout << "-??)";
        std::cout << std::endl;
    }
    return 0;
}
