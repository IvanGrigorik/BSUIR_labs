#include "Menu functions/Menu_functions.h"

int main() {

    std::vector<car::Car> car_v;



    while (true) {
        try {

            switch (get_menu_choice()) {

                case 1: {
                    add_car(car_v);
                    break;
                }

                case 2: {
                    show_cars(car_v);
                    system("pause > 0");
                    break;
                }

                case 3: {
                    sort_cars(car_v);
                    system("pause > 0");
                    break;
                }

                case 4: {
                    delete_duplicated(car_v);
                    system("pause > 0");
                    break;
                }

                case 5: {
                    copy_cars(car_v);
                    system("pause > 0");
                    break;
                }

                case 0:
                    exit(EXIT_SUCCESS);

            }

            system("cls");
        }
        catch (std::exception &ex) {
            std::cout << "Error: " << ex.what();
            system("pause > 0");
        }
    }
}

/* Ввод с клавиатуры
 * Массив объектов последнего класса
 * Сортировка по диапазону (для любого поля)
 * Перемещение подмассива в указанную позицию
 * Удаление дубликатов.
 */