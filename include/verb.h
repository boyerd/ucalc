#ifndef VERB_H
#define VERB_H

class mystreambuf: public std::streambuf
{
    public: 
        int threshold;
        mystreambuf(void) {threshold = 0;}
};
static mystreambuf nostreambuf;
static std::ostream nocout(&nostreambuf);
#define log(x) ((x >= nostreambuf.threshold)? std::cout : nocout)
#define setloglevel(x) nostreambuf.threshold = x
#define ERROR 0
#define BASIC 1
#define DETAIL 2


#endif //VERB_H

