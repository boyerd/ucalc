#ifndef LISTING_H
#define LISTING_H

class symbol;
class label;
class instruction;

class listing {
    private:
        std::vector<instruction*> *opstbl;
        std::vector<symbol*> *symtbl;
        std::vector<label*> *lbltbl;
    public:
        listing(void);
        ~listing(void);
        int factory(std::string);
        int addsymbol(std::string);
        void print(void);
};



#endif //LISTING_H
