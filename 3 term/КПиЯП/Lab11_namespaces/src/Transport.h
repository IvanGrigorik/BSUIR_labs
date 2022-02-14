/*
 * Created by Ivan on 19.11.2021.
 * BSUiR, 2021
 */

#pragma once

#include <iostream>

/*
 * Virtual abstract parent-class to class "car"
 */
class Transport {
public:

    std::string fabric{};

    Transport() = default;

    explicit Transport(const std::string& new_fabric);

    virtual ~Transport() = default;

    virtual void display() const = 0;

    std::string get_car_fabric() const;

    void set_fabric(const std::string &new_fabric);
};

