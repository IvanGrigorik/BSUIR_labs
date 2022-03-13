/*
 * Created by Ivan on 19.11.2021.
 * BSUiR, 2021
 */

#include "Transport.h"

// Constructor
Transport::Transport(const std::string& new_fabric) {
    set_fabric(new_fabric);
}

void Transport::set_fabric(const std::string &new_fabric) {
    fabric = new_fabric;
}

std::string Transport::get_car_fabric() const {
    return fabric;
}

void Transport::display() const {
    std::cout << get_car_fabric();
}
