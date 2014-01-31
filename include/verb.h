#ifndef VERB_H
#define VERB_H

class mystreambuf: public std::streambuf
{
    public: 
        int threshold;
        mystreambuf(void) {threshold = 0;}
};
mystreambuf nostreambuf;
std::ostream nocout(&nostreambuf);
#define log(x) ((x >= nostreambuf.threshold)? std::cout : nocout)
#define setloglevel(x) nostreambuf.threshold = x

#endif //VERB_H

