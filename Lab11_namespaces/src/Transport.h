/*
 * Created by Ivan on 19.11.2021.
 * BSUiR, 2021
 */

#pragma once

#include <iostream>

/*
 * Virtual parent-class to class "car"
 */
class Transport {
public:

    std::string fabric{};

    Transport() = default;

    explicit Transport(const std::string& new_fabric);

    virtual ~Transport() = default;

    virtual void display() const;

    std::string get_fabric() const;

    void set_fabric(const std::string &new_fabric);
};

