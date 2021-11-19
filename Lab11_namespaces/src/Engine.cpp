/*
 * Created by Ivan on 19.11.2021.
 * BSUiR, 2021
 */

#include "Engine.h"

Engine::Engine(const int &new_power, Engine_oil *new_engine_oil) {
    set_power(new_power);

    // Generate aggregation (engine_oil pointer point to new_engine_oil)
    engine_oil = new_engine_oil;
}

void Engine::display() const {
    std::cout << "Engine power: " << get_power() << std::endl
              << "Engine oil fabric: " << engine_oil->get_fabric() << std::endl;
}

int Engine::get_power() const {
    return power;
}

void Engine::set_power(const int &new_power) {
    power = new_power;
}


