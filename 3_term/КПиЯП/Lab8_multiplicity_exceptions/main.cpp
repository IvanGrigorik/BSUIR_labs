#include <iostream>
#include "Set.h"

void terminate() {
    std::cout << "Terminate called";
    abort ();
}

void unexpected() {
    std::cout << "Unexpected called" << std::endl;
    std::cout << "throw \"Error\"" << std::endl;
    throw "Error";
}

int main() {

    std::set_terminate (terminate);
    std::set_unexpected (unexpected);

    Set<int> new_set;

    while (true) {
        switch (get_menu_choice ()) {
            case 1:
                std::cout << "Enter number: ";
                try {
                    new_set.add (get_int (INT_MIN, INT_MAX));
                } catch (Set_ex &error) {
                    std::cout << "Error: " << error.what () << std::endl;
                    system ("pause>0");
                }
                break;

            case 2:
                try {
                    new_set.show ();
                } catch (Set_ex &error) {
                    std::cout << "Error: " << error.what () << std::endl;
                    system ("pause>0");
                }
                break;

            case 3:
                try {
                    new_set.search ();
                } catch (Set_ex &error) {
                    std::cout << "Error: " << error.what () << std::endl;
                    system ("pause>0");
                }
                break;

            case 4:
                try {
                    new_set.delete_element ();
                } catch (Set_ex &error) {
                    std::cout << "Error: " << error.what () << std::endl;
                    system ("pause>0");
                }
                break;

            case 5:
                try {
                    new_set.clear ();
                } catch (Set_ex &error) {
                    std::cout << "Error: " << error.what () << std::endl;
                    system ("pause>0");
                }
                break;

            case 6:
                try {
                    Set<int> result;
                    result = new_set + new_set;
                    result.show ();

                } catch (Set_ex &error) {
                    std::cout << "Error: " << error.what () << std::endl;
                    system ("pause>0");
                }
                break;

            case 7:
                // Shell sort
                try {
                    new_set.shell_sort ();
                } catch (Set_ex &error) {
                    std::cout << "Error: " << error.what () << std::endl;
                    system ("pause>0");
                }
                system ("pause > 0");
                break;

            case 8:
                try {
                    new_set.avg ();
                    system ("pause > 0");
                    break;
                } catch (Set_ex &error) {
                    std::cout << "Error: " << error.what () << std::endl;
                    system ("pause>0");
                }
                break;

            case 9:
                try {
                    new_set.change ();
                } catch (Set_ex &error) {
                    std::cout << "Error: " << error.what () << std::endl;
                    system ("pause>0");
                }
                break;

            case 0:
                exit (EXIT_SUCCESS);
        }
    }

}

// +Сортировка Шелла, +среднее значение массива (множество) (если дробное - error), +возможность редактирования.