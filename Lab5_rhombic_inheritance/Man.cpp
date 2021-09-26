//
// Created by Ivan on 25.09.2021.
//

#include "Man.h"

Man::Man (string new_name) : name(std::move(new_name)) {}

Man::~Man () {
    cout << "Man destructor called";
}

ostream &operator<< (ostream &os, const Man &man) {
    os << "Name: " << man.name;
    return os;
}