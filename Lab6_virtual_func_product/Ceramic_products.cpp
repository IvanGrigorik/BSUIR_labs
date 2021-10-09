//
// Created by Ivan on 03.10.2021.
//

#include "Ceramic_products.h"

Ceramic_products::Ceramic_products (float cost, int sell, const string &new_fabric) : Product(cost, sell) {
    set_fabric(new_fabric);
}

Ceramic_products::~Ceramic_products () {
    cout << "Ceramic product destructor called" << endl;
}

void Ceramic_products::set_fabric (const string &new_fabric) {
    this->fabric = new_fabric;
}

string Ceramic_products::get_fabric () const {
    return fabric;
}

void Ceramic_products::show () const {
    cout << "Cost: " << get_cost() << endl
         << "Cost with " << get_sell() << "% sell: " << sell_cost() << endl
         << "Fabric: " << get_fabric() << endl;
}

float Ceramic_products::sell_cost () const {
    return Product::sell_cost();
}



