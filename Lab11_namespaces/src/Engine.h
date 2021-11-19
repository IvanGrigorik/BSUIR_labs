/*
 * Created by Ivan on 19.11.2021.
 * BSUiR, 2021
 */

#pragma once

#include <iostream>

/*
 * Parent-class to car
 * Would be aggregation (self-existing object) in car
 */

class Engine {
protected:

    int power{};

public:

    Engine() = default;

    explicit Engine(int new_power);

    ~Engine() = default;

    virtual void display() const;

    int get_power() const;

    void set_power(const int &new_power);


};

