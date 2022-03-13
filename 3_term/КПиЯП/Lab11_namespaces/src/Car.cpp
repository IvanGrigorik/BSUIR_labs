/*
 * Created by Ivan on 19.11.2021.
 * BSUiR, 2021
 */

#include "Car.h"

// Good constructor
car::Car::Car(const std::string &new_fabric, const std::string &new_model, int new_power, Engine_oil *new_engine_oil,
              double new_radius, double new_lightning_range, double new_luminosity) : Transport(new_fabric) {

    set_model(new_model);

    engine.set_power(new_power);
    engine.engine_oil = new_engine_oil;

    wheel.set_radius(new_radius);

    headlight.set_lightning_range(new_lightning_range);
    headlight.set_luminosity(new_luminosity);

}

void car::Car::display() const {
    std::cout << "Fabric: " << get_car_fabric() << std::endl
              << "Model: " << get_model() << std::endl
              << "Engine power: " << engine.get_power() << std::endl
              << "Engine oil fabric: " << engine.engine_oil->get_fabric() << std::endl
              << "Wheel radius: " << wheel.get_radius() << std::endl
              << "Headlight lightning range: " << headlight.get_lightning_range() << std::endl
              << "Headlight lamp luminosity: " << headlight.get_luminosity() << std::endl;
}

std::string car::Car::get_model() const {
    return model;
}

void car::Car::set_model(const std::string &new_model) {
    model = new_model;
}
