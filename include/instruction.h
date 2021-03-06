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
        virtual void run(system_state* sys) {
            sys->pc += 1;
            std::cout << "Default run called :(" << std::endl;
        };

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
        void run(system_state* sys) {sys->pc += 1;};
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
        void run(system_state* sys) {sys->pc = (long)lbl;};
};

class jz: public instruction {
    public:
        jz(std::string input) : instruction(input) {}
        int ins(void) {
            return (2 << SHIFT);
        }
        void run(system_state* sys) {
            if (sys->a == 0)
                sys->pc += 2;
            else
                sys->pc += 1;
        };
};

class add: public direct {
    public:
        add(std::string input, int idx) : direct(input,idx) {}
        int ins(void) {
            return (3 << SHIFT) + symidx;
        }
        void run(system_state* sys) {
            sys->a += sys->rd_data(symidx);
            sys->pc += 1;
        };
};
    
class addi: public immediate {
    public:
        addi(std::string input, int val) : immediate(input,val) {}
        int ins(void) {
            return (4 << SHIFT) + value;
        }
        void run(system_state* sys) {
            sys->a += value;
            sys->pc += 1;
        };
};

class ldli : public immediate {
    public:
        ldli(std::string input, int val) : immediate(input,val) {
            value = (value & 0x0000FFFF);
        }
        int ins(void) {
            return (5 << SHIFT) + value;
        }
        void run(system_state* sys) {
            sys->a = (sys->a & 0xFFFF0000) | (value & 0x0000FFFF);
            sys->pc += 1;
        };
            
};

class ldhi : public immediate {
    public:
        ldhi(std::string input, int val) : immediate(input,val) {
            value = ((value >> 16) & 0x0000FFFF);
        }
        int ins(void) {
            return (6 << SHIFT) + value;
        }
        void run(system_state* sys) {
            sys->a = ((value << 16) & 0xFFFF0000) | (sys->a & 0x0000FFFF);
            sys->pc += 1;
        };
};

class st : public direct {
    public:
        st(std::string input,int idx) : direct(input,idx) {}
        int ins(void) {
            return (7 << SHIFT) + symidx;
        }
        void run(system_state* sys) {
            sys->wr_data(symidx,sys->a);
            sys->pc += 1;
        };
};

class ld : public direct {
    public:
        ld(std::string input,int idx) : direct(input,idx) {}
        int ins(void) {
            return (8 << SHIFT) + symidx;
        }
        void run(system_state* sys) {
            sys->a = sys->rd_data(symidx);
            sys->pc += 1;
        };
};

class sub: public direct {
    public:
        sub(std::string input, int idx) : direct(input,idx) {}
        int ins(void) {
            return (9 << SHIFT) + symidx;
        }
        void run(system_state* sys) {
            sys->a -= sys->rd_data(symidx);
            sys->pc += 1;
        };
};
    
class subi: public immediate {
    public:
        subi(std::string input, int val) : immediate(input,val) {}
        int ins(void) {
            return (10 << SHIFT) + value;
        }
        void run(system_state* sys) {
            sys->a -= value;
            sys->pc += 1;
        };
};

class logor: public direct {
    public:
        logor(std::string input, int idx) : direct(input,idx) {}
        int ins(void) {
            return (11 << SHIFT) + symidx;
        }
        void run(system_state* sys) {
            sys->a |= sys->rd_data(symidx);
            sys->pc += 1;
        };
};
    
class logori: public immediate {
    public:
        logori(std::string input, int val) : immediate(input,val) {}
        int ins(void) {
            return (12 << SHIFT) + value;
        }
        void run(system_state* sys) {
            sys->a |= value;
            sys->pc += 1;
        };
};

class logxor: public direct {
    public:
        logxor(std::string input, int idx) : direct(input,idx) {}
        int ins(void) {
            return (13 << SHIFT) + symidx;
        }
        void run(system_state* sys) {
            sys->a ^= sys->rd_data(symidx);
            sys->pc += 1;
        };
};
    
class logxori: public immediate {
    public:
        logxori(std::string input, int val) : immediate(input,val) {}
        int ins(void) {
            return (14 << SHIFT) + value;
        }
        void run(system_state* sys) {
            sys->a ^= value;
            sys->pc += 1;
        };
};

class logand: public direct {
    public:
        logand(std::string input, int idx) : direct(input,idx) {}
        int ins(void) {
            return (15 << SHIFT) + symidx;
        }
        void run(system_state* sys) {
            sys->a &= sys->rd_data(symidx);
            sys->pc += 1;
        };
};
    
class logandi: public immediate {
    public:
        logandi(std::string input, int val) : immediate(input,val) {}
        int ins(void) {
            return (16 << SHIFT) + value;
        }
        void run(system_state* sys) {
            sys->a &= value;
            sys->pc += 1;
        };
};

class lognot: public instruction {
    public:
        lognot(std::string input) : instruction(input) {}
        int ins(void) {
            return (17 << SHIFT);
        }
        void run(system_state* sys) {
            sys->a = ~sys->a;
            sys->pc += 1;
        };
};

class fin: public instruction {
    public:
        fin(std::string input) : instruction(input) {}
        int ins(void) {
            return (18 << SHIFT);
        }
        void run(system_state* sys) {}
};

#endif //INSTRUCTION_H
