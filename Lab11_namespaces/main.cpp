#include <iostream>
#include "src/Car.h"

int main() {

    auto *engine_oil = new Engine_oil("Engine oil fabric");

    car::Car car("Car_fabric", "Car_model", 1000, engine_oil, 30, 100, 3000);

    car.display();

}
