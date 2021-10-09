//
// Created by Ivan on 28.09.2021.
//

#include "Dairy_products.h"

Dairy_products::Dairy_products (float cost, int sell, int new_fermentation_period) : Product(cost, sell) {
    set_fermentation_period(new_fermentation_period);
}

Dairy_products::~Dairy_products () {
    cout << "Dairy product destructor called" << endl;
}

void Dairy_products::set_fermentation_period (const int &new_fermentation_period) {
    this->fermentation_period = new_fermentation_period;
}

int Dairy_products::get_fermentation_period () const {
    return fermentation_period;
}

void Dairy_products::show () const {
    cout << "Cost: " << get_cost() << endl
         << "Cost with " << get_sell() <<  "% sell: " << sell_cost() << endl
         << "Fermentation period: " << get_fermentation_period() << endl;
}

float Dairy_products::sell_cost () const {
    return Product::sell_cost();
}
