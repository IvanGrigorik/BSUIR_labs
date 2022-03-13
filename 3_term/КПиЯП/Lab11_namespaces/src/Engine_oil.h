/*
 * Created by Ivan on 19.11.2021.
 * BSUiR, 2021
 */

#pragma once

#include <iostream>

/*
 * Self-existing-class.
 * Would be aggregated into class "Engine".
 */

class Engine_oil {
protected:

    std::string fabric{};

public:

    Engine_oil() = default;

    explicit Engine_oil(const std::string &new_fabric);

    virtual ~Engine_oil() = default;

    virtual void display() const;

    std::string get_fabric() const;

    void set_fabric(const std::string &new_fabric);
};

