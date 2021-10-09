//
// Created by Ivan on 28.09.2021.
//

#include "Product.h"

Product::Product (float new_cost, int new_sell) {
    cout << "Product constructor called" << endl;
    set_cost(new_cost);
    set_sell(new_sell);
}

Product::~Product () {
    cout << "Product destructor called" << endl;
}

void Product::set_cost (const float &new_cost) {
    this->cost = new_cost;
}

float Product::get_cost () const {
    return cost;
}

void Product::set_sell (const int &new_sell) {
    this->sell = new_sell;
}

int Product::get_sell () const {
    return sell;
}

float Product::sell_cost () const {
    return (cost - (cost * (static_cast<float>(get_sell()) / 100)));
}




