//
// Created by Ivan on 25.09.2021.
//

#ifndef LAB_5_RHOMBIC_INHERITANCE_MAN_H
#define LAB_5_RHOMBIC_INHERITANCE_MAN_H

#include <iostream>

using namespace std;

void get_int (int &y, int max_size);

class Man {
protected:
    string name{};

public:
    explicit Man (string new_name);

    virtual ~Man ();

    void set_name (string name);

    void re_name ();

    friend ostream &operator<< (ostream &os, const Man &man);

};


#endif //LAB_5_RHOMBIC_INHERITANCE_MAN_H
