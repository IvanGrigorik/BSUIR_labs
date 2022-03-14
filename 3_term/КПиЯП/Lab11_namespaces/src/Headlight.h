/*
 * Created by Ivan on 19.11.2021.
 * BSUiR, 2021
 */

#pragma once

#include "Lamp.h"

/*
 * Self-existing class.
 * Would be inhered into class "car".
 */

class Headlight : public Lamp {
protected:

    double lightning_range{};

public:

    Headlight() = default;

    explicit Headlight(double new_lightning_range, double new_luminosity);

    ~Headlight() override = default;

    void display() const override;

    double get_lightning_range() const;

    void set_lightning_range(const double &new_lightning_range);
};