#include <iostream>
#include "Set.h"
#include "menu_functions.h"

void terminate() {
    std::cout << "terminate called";
    abort ();
}

void unexpected() {
    std::cout << "unexpected called" << std::endl;
    std::cout << "throw 123" << std::endl;
    throw 123;
}



int main() {

    std::set_terminate (terminate);
    std::set_unexpected (unexpected);

    Set<int> new_set;

    while (true)
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
                system ("pause > 0");
                system ("cls");
                break;

            case 3:
                new_set.search ();
                break;

            case 0:
                exit (EXIT_SUCCESS);


            default:
                exit (-1);

        }

    std::cout << "This line is never printed";
}
