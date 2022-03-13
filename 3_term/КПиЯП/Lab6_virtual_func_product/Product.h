//
// Created by Ivan on 28.09.2021.
//

#ifndef LAB6_VIRTUAL_FUNC_PRODUCT_PRODUCT_H
#define LAB6_VIRTUAL_FUNC_PRODUCT_PRODUCT_H

#include <iostream>

using namespace std;

class Product {
public:
    float cost{};

    int sell{};

    explicit Product(float, int);

    virtual ~Product() = 0;

    void set_cost(const float &new_cost);

    float get_cost() const;

    void set_sell(const int &new_sell);

    int get_sell() const;

    virtual void show() const = 0;

    virtual float sell_cost() const = 0;
};


#endif //LAB6_VIRTUAL_FUNC_PRODUCT_PRODUCT_H
