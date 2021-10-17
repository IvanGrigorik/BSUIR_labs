//
// Created by Ivan on 25.09.2021.
//

#include "Man.h"

Man::Man (string new_name) {
    cout << "Man constructor called" << endl;
    set_name(std::move(new_name));
}

Man::~Man () {
    cout << "Man destructor called";
}

ostream &operator<< (ostream &os, const Man &man) {
    os << "Name: " << man.name;
    return os;
}

void Man::set_name (string new_name) {
    this->name = std::move(new_name);
}

void Man::re_name () {
    cout << "Enter new name: ";
    string new_name{};
    cin >> new_name;
    set_name(new_name);
}