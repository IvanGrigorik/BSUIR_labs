/*
 * Created by Ivan on 19.11.2021.
 * BSUiR, 2021
 */

#include "Transport.h"

// Constructor
Transport::Transport(double new_weight) {
    set_weight(new_weight);
}

void Transport::set_weight(const double &new_weight) {
    weight = new_weight;
}

double Transport::get_weight() const {
    return weight;
}

void Transport::display() const {
    std::cout << get_weight();
}
