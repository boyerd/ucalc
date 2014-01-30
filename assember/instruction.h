#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <stdlib.h>

const int SHIFT = 24;

std::string argify(const std::string&);

class instruction {
    protected:
    public:
        std::string mnemonic;
        instruction(std::string input): mnemonic(input) {}
        virtual int ins() = 0;
};

class immediate : public instruction {
    public:
        int value;
        immediate(std::string input) : instruction(input) {
            value = strtol(argify(input).c_str(),NULL,0);
        };
        virtual int ins() = 0;
};

class direct : public instruction {
    public:
        int symidx;
        direct(std::string input, int idx) : instruction(input) {
            symidx = idx;
        };
        virtual int ins() = 0;
};
            
    
class nop: public instruction {
    public:
        nop(std::string input) : instruction(input) {}
        int ins(void) {
            return (0 << SHIFT);
        }
};

class clr: public instruction {
    public:
        clr(std::string input) : instruction(input) {}
        int ins(void) {
            return (1 << SHIFT);
        }
};

class jz: public instruction {
    public:
        jz(std::string input) : instruction(input) {}
        int ins(void) {
            return (2 << SHIFT);
        }
};

class add: public direct {
    public:
        add(std::string input, int idx) : direct(input,idx) {}
        int ins(void) {
            return (3 << SHIFT) + symidx;
        }
};
    
class addi: public immediate {
    public:
        addi(std::string input) : immediate(input) {}
        int ins(void) {
            return (4 << SHIFT) + value;
        }
};

class ldli : public immediate {
    public:
        ldli(std::string input) : immediate(input) {
            value = (value & 0x0000FFFF);
        }
        int ins(void) {
            return (5 << SHIFT) + value;
        }
};

class ldhi : public immediate {
    public:
        ldhi(std::string input) : immediate(input) {
            value = (value & 0x0000FFFF);
        }
        int ins(void) {
            return (6 << SHIFT) + value;
        }
};

class ref : public direct {
    public:
        ref(std::string input,int idx) : direct(input,idx) {}
        int ins(void) {
            return 0;
        }
};

int instruction_factory(std::string, std::vector<instruction*>&);
int instruction_optimize(std::vector<instruction*>&);

#endif //INSTRUCTION_H
