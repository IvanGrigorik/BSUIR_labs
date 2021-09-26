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
    explicit Man (string new_name);

    virtual ~Man ();

    friend ostream &operator<< (ostream &os, const Man &man);

};


#endif //LAB_5_RHOMBIC_INHERITANCE_MAN_H
