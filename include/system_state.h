#ifndef SYSTEM_STATE_H
#define SYSTEM_STATE_H

class system_state {
    public:
        int pc;
        int a;
        void wr_data(int addr, int val) {
            if (addr > (int)data.size()-1)
                data.resize(addr+1,0);
            data[addr] = val;
        }
        int rd_data(int addr) {
            if (addr > (int)data.size()-1)
                data.resize(addr+1,0);
            return data[addr];
        }
        int sz_data(void) {
            return data.size();
        }
    private:
        std::vector<int> data;
};

#endif // SYSTEM_STATE_H

