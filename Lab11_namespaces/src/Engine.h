/*
 * Created by Ivan on 19.11.2021.
 * BSUiR, 2021
 */

#pragma once

#include <iostream>
#include "Engine_oil.h"

/*
 * Self-existing-class.
 * Would be inhered into class "car".
 */

class Engine {
protected:

    int power{};

public:
    // Aggregation pointer
    Engine_oil *engine_oil{};

public:

    Engine() = default;

    explicit Engine(const int &new_power, Engine_oil *new_engine_oil);

    virtual ~Engine() = default;

    virtual void display() const;

    int get_power() const;

    void set_power(const int &new_power);
};

