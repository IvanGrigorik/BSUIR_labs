/*
 * Created by Ivan on 19.11.2021.
 * BSUiR, 2021
 */

#include "Engine.h"

Engine::Engine(int new_power) {
    set_power(new_power);
}

void Engine::display() const {
    std::cout << get_power();
}

int Engine::get_power() const {
    return power;
}

void Engine::set_power(const int &new_power) {
    power = new_power;
}


