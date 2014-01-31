#ifndef SYMBOL_H
#define SYMBOL_H

class symbol {
    public:
        std::string name;
        symbol(void) {
            name = "";
        }
        symbol(std::string input) {
            name = input;
        }
};

#endif //SYMBOL_H

