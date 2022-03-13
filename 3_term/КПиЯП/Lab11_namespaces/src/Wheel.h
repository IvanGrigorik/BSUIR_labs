/*
 * Created by Ivan on 19.11.2021.
 * BSUiR, 2021
 */

#pragma once

#include <iostream>

class Wheel {

protected:
    double radius{};

public:

    Wheel() = default;

    explicit Wheel(double new_radius);

    virtual void display() const;

    double get_radius() const;

    void set_radius(const double &new_radius);

};

