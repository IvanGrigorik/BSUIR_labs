/*
 * Created by Ivan on 19.11.2021.
 * BSUiR, 2021
 */

#pragma once

#include "Headlight.h"
#include "Engine.h"
#include "Transport.h"
#include "Wheel.h"

namespace car {
    class Car final : public Transport {

    protected:

        std::string model{};
        Headlight headlight;
        Engine engine;
        Wheel wheel;


    public:

        Car() = default;

        Car(const std::string &new_fabric, const std::string &new_model, int new_power, Engine_oil *new_engine_oil,
            double new_radius, double new_lightning_range, double new_luminosity);

        ~Car() final = default;

        void display() const final;

        std::string get_model() const;

        void set_model(const std::string &new_model);

    };

}