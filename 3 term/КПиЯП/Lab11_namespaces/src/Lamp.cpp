/*
 * Created by Ivan on 19.11.2021.
 * BSUiR, 2021
 */

#include "Lamp.h"

Lamp::Lamp(double new_luminosity) {
    set_luminosity(new_luminosity);
}

void Lamp::display() const {
    std::cout << get_luminosity();
}

double Lamp::get_luminosity() const {
    return luminosity;
}

void Lamp::set_luminosity(const double &new_luminosity) {
    luminosity = new_luminosity;
}
