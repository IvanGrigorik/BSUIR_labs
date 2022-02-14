/*
 * Created by Ivan on 19.11.2021.
 * BSUiR, 2021
 */

#pragma once

#include <iostream>

/*
 * Self-existing class.
 * Would be inhered into class "Headlight".
 */

class Lamp {
protected:


    double luminosity{};

public:
    Lamp() = default;

    virtual ~Lamp() = default;

    explicit Lamp(double new_luminosity);

    virtual void display() const;

    double get_luminosity() const;

    void set_luminosity(const double &new_luminosity);
};

