#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "system_state.h"

const int SHIFT = 24;
class label;
class symbol;
class system_state;

std::string argify(const std::string&);

class instruction {
    protected:
    public:
        std::string mnemonic;
        instruction(std::string input): mnemonic(input) {}
        virtual int ins() = 0;
        void run(system_state*, int data) {};
};

class immediate : public instruction {
    public:
        int value;
        immediate(std::string input, int val) : instruction(input) {
            //value = strtol(argify(input).c_str(),NULL,0);
            value = val;
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

class jump : public instruction {
    public:
        label* lbl;
        jump(std::string input, label* targ) : instruction(input) {
            lbl = targ;
        }
        int ins(void) {
            return (1 << SHIFT) + lbl->op_id;
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
        addi(std::string input, int val) : immediate(input,val) {}
        int ins(void) {
            return (4 << SHIFT) + value;
        }
};

class ldli : public immediate {
    public:
        ldli(std::string input, int val) : immediate(input,val) {
            value = (value & 0x0000FFFF);
        }
        int ins(void) {
            return (5 << SHIFT) + value;
        }
};

class ldhi : public immediate {
    public:
        ldhi(std::string input, int val) : immediate(input,val) {
            value = ((value >> 16) & 0x0000FFFF);
        }
        int ins(void) {
            return (6 << SHIFT) + value;
        }
};

class st : public direct {
    public:
        st(std::string input,int idx) : direct(input,idx) {}
        int ins(void) {
            return (7 << SHIFT) + symidx;
        }
};

class ld : public direct {
    public:
        ld(std::string input,int idx) : direct(input,idx) {}
        int ins(void) {
            return (8 << SHIFT) + symidx;
        }
};

class sub: public direct {
    public:
        sub(std::string input, int idx) : direct(input,idx) {}
        int ins(void) {
            return (9 << SHIFT) + symidx;
        }
};
    
class subi: public immediate {
    public:
        subi(std::string input, int val) : immediate(input,val) {}
        int ins(void) {
            return (10 << SHIFT) + value;
        }
};

//int instruction_factory(std::string, std::vector<instruction*>&);
//int instruction_optimize(std::vector<instruction*>&);

#endif //INSTRUCTION_H
