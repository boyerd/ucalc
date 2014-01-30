#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

class instruction;

class symbol {
    public:
        std::string name; 
        int first_use;
        int last_use;
        symbol(std::string input) {
            name = input;
            first_use = -1;
            last_use = -1;
        };
};

class symboltable {
    private:
        std::vector<symbol> table;
    public:
        int add_symbol(std::string);
        int merge_symbols(std::vector<instruction*>&);
        int print_symbols(void);
};

#endif //SYMBOLTABLE_H
