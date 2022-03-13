//
// Created by Ivan on 28.09.2021.
//

#ifndef LAB6_VIRTUAL_FUNC_PRODUCT_DAIRY_PRODUCTS_H
#define LAB6_VIRTUAL_FUNC_PRODUCT_DAIRY_PRODUCTS_H

#include "Product.h"

class Dairy_products : public Product {
protected:
    int fermentation_period{};

public:

    Dairy_products (float cost, int sell, int new_fermentation_period);

    ~Dairy_products () override;

    void set_fermentation_period (const int &new_fermentation_period);

    int get_fermentation_period () const;

    void show () const override;

    float sell_cost () const override;
};


#endif //LAB6_VIRTUAL_FUNC_PRODUCT_DAIRY_PRODUCTS_H
