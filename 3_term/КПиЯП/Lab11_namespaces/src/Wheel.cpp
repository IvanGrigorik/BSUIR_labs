/*
 * Created by Ivan on 19.11.2021.
 * BSUiR, 2021
 */

#include "Wheel.h"

Wheel::Wheel(double new_radius) {
    set_radius(new_radius);
}

void Wheel::display() const {
    std::cout << get_radius();
}

double Wheel::get_radius() const {
    return radius;
}

void Wheel::set_radius(const double &new_radius) {
    radius = new_radius;
}
