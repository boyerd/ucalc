#ifndef LABEL_H
#define LABEL_H

class label {
    public:
        std::string name;
        int op_id; 
        label(void) {
            name = "";
            op_id = -1;
        }
        label(std::string input, int id) {
            name = input;
            op_id = id;
        }
                
};

#endif //LABEL_H

