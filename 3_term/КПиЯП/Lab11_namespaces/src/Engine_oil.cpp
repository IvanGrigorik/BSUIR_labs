/*
 * Created by Ivan on 19.11.2021.
 * BSUiR, 2021
 */

#include "Engine_oil.h"

Engine_oil::Engine_oil(const std::string &new_fabric) {
    set_fabric(new_fabric);
}

void Engine_oil::display() const {
    std::cout << get_fabric();
}

std::string Engine_oil::get_fabric() const {
    return fabric;
}

void Engine_oil::set_fabric(const std::string &new_fabric) {
    fabric = new_fabric;
}
