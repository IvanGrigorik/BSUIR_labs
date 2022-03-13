//
// Created by Ivan on 03.10.2021.
//

#ifndef MAIN_CPP_CERAMIC_PRODUCTS_H
#define MAIN_CPP_CERAMIC_PRODUCTS_H

#include "Product.h"

class Ceramic_products final : public Product {
private:
    string fabric{};

public:

    Ceramic_products (float cost, int sell, const string& new_fabric);

    ~Ceramic_products () override;

    void set_fabric (const string &new_fabric);

    string get_fabric () const;

    void show () const final;

    float sell_cost () const override;
};


#endif //MAIN_CPP_CERAMIC_PRODUCTS_H
