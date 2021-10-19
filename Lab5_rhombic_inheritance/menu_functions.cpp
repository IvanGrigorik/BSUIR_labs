//
// Created by Ivan on 04.10.2021.
//

#include "menu_functions.h"

int get_menu_choice () {
    system("cls");
    cout << "Enter what you want to enter: " <<
         endl << "1) Change something " <<
         endl << "2) Show people " <<
         endl << "0) Exit" <<
         endl << ">> ";

    int choice = get_int(2);
    return choice;
}

int get_change_person_class (Student_Programmer const &person) {
    cout << endl << "Person: " << endl << person;

    cout
            << endl
            << "Enter what you want to change: " << endl
            << "1) Name" << endl
            << "2) Salary" << endl
            << "3) Programming language" << endl
            << "4) GPA" << endl
            << "5) Term" << endl
            << "6) University programming language" << endl
            << "0) Exit" << endl << ">> ";

    int choice = get_int(6);
    return choice;
}

void get_Student_programmer_data (Student_Programmer &person) {
    cout << "Enter name: ";
    person.set_name(get_string("name"));

    cout << "Enter salary: ";
    person.set_salary(get_int(5000));

    cout << "Enter programming language: ";
    string PL;
    cin >> PL;
    person.set_programming_language(PL);

    cout << "Enter GPA: ";
    person.set_GPA(get_int(10));

    cout << "Enter term: ";
    person.set_term(get_int(4));

    cout << "Enter university programming language: ";
    cin >> PL;
    person.set_university_program_language(PL);
}

void change_Student_programmer_field (Student_Programmer &person) {

    switch (get_change_person_class(person)) {
        case 1:
            person.re_name();
            break;
        case 2:
            person.re_salary();
            break;
        case 3:
            person.re_programming_language();
            break;
        case 4:
            person.re_GPA();
            break;
        case 5:
            person.re_term();
            break;
        case 6:
            person.re_university_programming_language();
            break;
        default:
            cout << "Invalid input";
            break;
    }
}
