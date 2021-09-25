//
// Created by Ivan on 25.09.2021.
//

#ifndef LAB_5_RHOMBIC_INHERITANCE_MAN_H
#define LAB_5_RHOMBIC_INHERITANCE_MAN_H

#include <iostream>

using namespace std;

class Man {
protected:
    string name{};

public:
    Man () : name() {};

    Man (string new_name) : name(std::move(new_name)) {};

    ~Man () = default;

    void show_name() {
        cout << name;
    };
};


#endif //LAB_5_RHOMBIC_INHERITANCE_MAN_H
