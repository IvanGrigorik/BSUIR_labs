//
// Created by Ivan on 25.09.2021.
//

#pragma once

#include <iostream>
#include "getters.h"

using namespace std;

class Man {
protected:
    string name{};

public:
    Man () = default;

    explicit Man (string new_name);

    virtual ~Man ();

    void set_name (string name);

    void re_name ();

    friend ostream &operator<< (ostream &os, const Man &man);
};


