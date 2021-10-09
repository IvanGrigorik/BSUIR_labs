//
// Created by Ivan on 28.09.2021.
//

#ifndef LAB6_VIRTUAL_FUNC_PRODUCT_CHEESE_H
#define LAB6_VIRTUAL_FUNC_PRODUCT_CHEESE_H

#include "Dairy_products.h"

class Cheese final : public Dairy_products {
private:
    string production_country {};

public:
    Cheese(float cost, int sell, int fermentation_period, string new_country);

    ~Cheese() final;

    void set_country(string &new_country);

    string get_country() const;

    void show() const final;

    float sell_cost () const override;

};


#endif //LAB6_VIRTUAL_FUNC_PRODUCT_CHEESE_H
