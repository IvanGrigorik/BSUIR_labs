/*
 * Created by Ivan on 29.11.2021.
 * BSUiR, 2021
 */

#include "Menu_functions.h"

int get_menu_choice() {
    system("cls");
    std::cout << "Enter what you want to : " << std::endl
              << "1) Add new car" << std::endl
              << "2) Show cars" << std::endl
              << "3) Sort cars by parameters" << std::endl
              << "4) Delete duplicated cars" << std::endl
              << "5) Move cars" << std::endl
              << "0) Exit" << std::endl
              << ">> ";
    int choice = get_int(0, 5);
    return choice;
}

int get_int(int min_size, int max_size) {
    int x;
    while (true) {
        std::cin >> x;

        if (std::cin.fail() || std::cin.peek() != '\n' || x < min_size || x > max_size) {
            std::cout << "Invalid input, try again" << std::endl << ">> ";
            std::cin.clear();
            std::cin.ignore(32768, '\n');
        } else {
            return x;
        }
    }
}

void add_car(std::vector<car::Car> &car_v) {
    std::string car_model, oil_fabric, transport_fabric;
    int engine_power;
    double wheel_radius, lamp_luminosity, headlight_lightning_range;

    std::cout << "Car fabric: ";
    std::cin >> transport_fabric;
    std::cout << "Car model: ";
    std::cin >> car_model;
    std::cout << "Engine power: ";
    engine_power = get_int(0, 1000);
    std::cout << "Oil fabric: ";
    std::cin >> oil_fabric;
    std::cout << "Wheel radius: ";
    wheel_radius = get_int(0, 50);
    std::cout << "Lightning range: ";
    headlight_lightning_range = get_int(0, 1000);
    std::cout << "Luminosity: ";
    lamp_luminosity = get_int(0, 1000);

    auto *engine_oil = new Engine_oil(oil_fabric);

    car::Car new_car(transport_fabric, car_model, engine_power, engine_oil, wheel_radius, headlight_lightning_range,
                     lamp_luminosity);

    car_v.push_back(new_car);
}

void show_cars(std::vector<car::Car> &car_v) {

    if (car_v.empty()) {
        throw std::runtime_error("Not a single car is created");
    }

    for (int i = 0; i < car_v.size(); i++) {
        std::cout << "Car " << i + 1 << ":" << std::endl;
        car_v[i].display();
        std::cout << std::endl;
    }

}

void sort_cars(std::vector<car::Car> &car_v) {
    if (car_v.empty()) {
        throw std::runtime_error("Not a single car is created");
    }

    std::cout << "Enter by what you want sort: " << std::endl
              << "1) By car fabric" << std::endl
              << "2) By car model" << std::endl
              << "3) By engine power" << std::endl
              << "4) By oil fabric" << std::endl
              << "5) By wheel radius" << std::endl
              << "6) By headlight lightning range" << std::endl
              << "7) By lamp luminosity" << std::endl;

    int choice = get_int(0, 7);

    if (choice == 1 || choice == 2 || choice == 4) {
        sort_string(car_v, choice);
    } else if (choice == 3 || choice == 5 || choice == 6 || choice == 7) {
        sort_num(car_v, choice);
    }
    std::cout << "Sorted";
}

void sort_string(std::vector<car::Car> &car_v, int choice) {
    for (int i = 0; i < car_v.size() - 1; i++) {
        for (int j = i + 1; j < car_v.size(); j++) {

            switch (choice) {
                case 1: {
                    if (car_v[i].get_car_fabric() > car_v[j].get_car_fabric()) {
                        std::swap(car_v[i], car_v[j]);
                    }
                    break;
                }

                case 2: {
                    if (car_v[i].get_model() > car_v[j].get_model()) {
                        std::swap(car_v[i], car_v[j]);
                    }
                    break;
                }
                case 4: {
                    if (car_v[i].engine.get_power() > car_v[j].engine.get_power()) {
                        std::swap(car_v[i], car_v[j]);
                    }
                    break;
                }

                default:
                    break;
            }
        }
    }
}

void sort_num(std::vector<car::Car> &car_v, int choice) {
    for (int i = 0; i < car_v.size() - 1; i++) {
        for (int j = i + 1; j < car_v.size(); j++) {

            switch (choice) {

                case 3: {
                    if (car_v[i].engine.get_power() > car_v[j].engine.get_power()) {
                        std::swap(car_v[i], car_v[j]);
                    }
                    break;
                }

                case 5: {
                    if (car_v[i].wheel.get_radius() > car_v[j].wheel.get_radius()) {
                        std::swap(car_v[i], car_v[j]);
                    }
                    break;
                }

                case 6: {
                    if (car_v[i].headlight.get_lightning_range() > car_v[j].headlight.get_lightning_range()) {
                        std::swap(car_v[i], car_v[j]);
                    }
                    break;
                }

                case 7: {
                    if (car_v[i].headlight.get_luminosity() > car_v[j].headlight.get_luminosity()) {
                        std::swap(car_v[i], car_v[j]);
                    }
                    break;
                }

                default:
                    break;
            }
        }
    }
}

void delete_duplicated(std::vector<car::Car> &car_v) {
    for (int i = 0; i < car_v.size() - 1; i++) {
        for (int j = i + 1; j < car_v.size(); j++) {

            if (compare_cars(car_v[i], car_v[j]) == 0) {

                for (int k = j; k < car_v.size() - 1; k++) {
                    std::swap(car_v[k], car_v[k + 1]);
                }

                car_v.pop_back();
                --j;
            }
        }
    }

    std::cout << "Duplicated cars deleted";
}

// Return 0, if cars equal
int compare_cars(car::Car &car1, car::Car &car2) {
    if (car1.get_car_fabric() == car2.get_car_fabric() &&
        car1.get_model() == car2.get_model() &&
        car1.engine.get_power() == car2.engine.get_power() &&
        car1.engine.engine_oil->get_fabric() == car2.engine.engine_oil->get_fabric() &&
        car1.wheel.get_radius() == car2.wheel.get_radius() &&
        car1.headlight.get_lightning_range() == car2.headlight.get_lightning_range() &&
        car1.headlight.get_luminosity() == car2.headlight.get_luminosity()) {
        return 0;
    }
    return 1;
}


void copy_cars(std::vector<car::Car> &car_v) {

    show_cars(car_v);

    std::vector<car::Car> temp1, temp2;

    int first_pos, second_pos, move_pos;
    std::cout << "Enter first position: ";
    first_pos = get_int(0, static_cast<int>(car_v.size())) - 1; // -1 to indexing
    std::cout << "Enter second position: ";
    second_pos = get_int(0, static_cast<int>(car_v.size())) - 1; // -1 to indexing
    std::cout << "Enter move position: ";
    move_pos = get_int(0, static_cast<int>(car_v.size())) - 1;


    if (move_pos >= first_pos && move_pos <= second_pos) {
        throw std::runtime_error("Invalid index");
    }

    for (int i = first_pos; i < second_pos + 1; i++) {
        temp1.push_back(car_v[i]);
    }

    if (first_pos < move_pos) {
        move_pos++;
    }

    for (int i = 0; i < car_v.size() + 1; i++) {

        if (i >= first_pos && i <= second_pos) {
            continue;
        } else if (i == move_pos) {

            for (int j = 0; j < temp1.size(); j++) {
                temp2.push_back(temp1[j]);
            }

        }
        if (car_v.size() != i) {
            temp2.push_back(car_v[i]);
        }
    }

    car_v = temp2;

    std::cout << "Cars moved" << std::endl;
}