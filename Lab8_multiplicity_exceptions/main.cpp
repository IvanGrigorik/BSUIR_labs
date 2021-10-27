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

// При вводе посмотреть, чтобы не было одинакового значения(т.к. это множество).

int main() {

    std::set_terminate (terminate);
    std::set_unexpected (unexpected);

    Set<int> new_set;
    Set<char> another_set;

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
                system ("cls");
                break;

            case 2:
                new_set.show ();
                system ("cls");
                break;

            case 3:
                new_set.search ();
                break;

            case 4:
                new_set.delete_element ();
                break;

            case 5:
                new_set.clear ();
                break;

            case 6:
                std::cout << "Enter number: ";
                try {
                    char new_obj;
                    std::cin >> new_obj;
                    another_set.add (new_obj);
                } catch (Set_ex &error) {
                    std::cout << "Error: " << error.what () << std::endl;
                    system ("pause>0");
                }
                system ("cls");
                break;

            case 7:
                try {
                    Set<int> result;
                    result = new_set + new_set;
                    result.show ();

                } catch (Set_ex &error) {
                    std::cout << "Error: " << error.what () << std::endl;
                    system ("pause>0");
                }
                break;

            case 0:
                exit (EXIT_SUCCESS);
        }
    }

    std::cout << "This line is never printed";
}
