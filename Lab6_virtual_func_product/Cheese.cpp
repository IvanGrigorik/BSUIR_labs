//
// Created by Ivan on 28.09.2021.
//

#include "Cheese.h"

Cheese::Cheese (float cost, int sell, int fermentation_period, string new_country) :
        Dairy_products(cost, sell, fermentation_period) {
    set_country(new_country);
}

Cheese::~Cheese () {
    cout << "Cheese destructor called" << endl;
}

void Cheese::set_country (string &new_country) {
    production_country = new_country;
}

string Cheese::get_country () const {
    return production_country;
}

float Cheese::sell_cost () const {
    return Dairy_products::sell_cost();
}

void Cheese::show () const {
    Dairy_products::show();
    cout << "Cheese production country: " << get_country() << endl;
}



