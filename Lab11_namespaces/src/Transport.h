/*
 * Created by Ivan on 19.11.2021.
 * BSUiR, 2021
 */

#pragma once

#include <iostream>

/*
 * Virtual parent-class to other classes
 */
class Transport {
public:

    double weight{};

    Transport() = default;

    explicit Transport(double new_weight);

    virtual ~Transport() = 0;

    virtual void display() const;

    double get_weight() const;

    void set_weight(const double &new_weight);
};

