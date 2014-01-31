#ifndef SYSTEM_STATE_H
#define SYSTEM_STATE_H

class system_state {
    public:
        std::vector<int> data;
        std::vector<int> rom;
        int pc;
        int a;
};

#endif // SYSTEM_STATE_H

