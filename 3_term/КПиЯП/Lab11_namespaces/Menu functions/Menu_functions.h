/*
 * Created by Ivan on 29.11.2021.
 * BSUiR, 2021
 */

#pragma once

#include <iostream>
#include <vector>
#include "../src/Car.h"

int get_menu_choice();

int get_int(int min_size, int max_size);

void add_car(std::vector<car::Car> &car_v);

void show_cars(std::vector<car::Car> &car_v);

void sort_cars(std::vector<car::Car> &car_v);

void sort_string(std::vector<car::Car> &car_v, int choice);

void sort_num(std::vector<car::Car> &car_v, int choice);

void delete_duplicated(std::vector<car::Car> &car_v);

int compare_cars(car::Car &car1, car::Car &car2);

void copy_cars(std::vector<car::Car> &car_v);