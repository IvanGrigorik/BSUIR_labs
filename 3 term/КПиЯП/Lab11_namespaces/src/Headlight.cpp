/*
 * Created by Ivan on 19.11.2021.
 * BSUiR, 2021
 */

#include "Headlight.h"

Headlight::Headlight(double new_light_range, double new_luminosity) : Lamp(new_luminosity) {
    set_lightning_range(new_light_range);
}

void Headlight::display() const {
    std::cout << get_lightning_range() << ' ';
    Lamp::display();
}

double Headlight::get_lightning_range() const {
    return lightning_range;
}

void Headlight::set_lightning_range(const double &new_lightning_range) {
    lightning_range = new_lightning_range;
}