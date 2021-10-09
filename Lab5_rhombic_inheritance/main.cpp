#include "Student_Programmer.h"
#include "menu_functions.h"

string input_string (const string &code);

int main () {

    int salary{}, GPA{}, term{};
    string name{}, programming_language{}, university_programming_language{};

    cout << "Enter name: ";
    name = input_string("name"); // Сделать проверку
    cout << "Enter salary: ";
    get_int(salary, 5000);
    cout << "Enter programming language: ";
    programming_language = input_string("");
    cout << "Enter GPA: ";
    get_int(GPA, 10);
    cout << "Enter term: ";
    get_int(term, 4);
    cout << "Enter university programming language: ";
    university_programming_language = input_string("");
    Student_Programmer people{name, salary, programming_language, GPA, term, university_programming_language};


    while (true) {
        switch (get_menu_choice()) {

            case 1:
                switch (get_change_people_class()) {
                    case 1:
                        people.re_name();
                        break;
                    case 2:
                        people.re_salary();
                        break;
                    case 3:
                        people.re_programming_language();
                        break;
                    case 4:
                        people.re_GPA();
                        break;
                    case 5:
                        people.re_term();
                        break;
                    case 6:
                        people.re_university_programming_language();
                        break;
                    default:
                        cout << "Invalid input";
                        break;
                }
                break;

            case 2:
                cout << people;
                system("pause > 0");
                break;


            case 0:
                return 0;

        }
    }
}

string input_string (const string &code) {
    string new_string;
    while (true) {
        cin >> new_string;
        if (cin.fail() || cin.bad()) {
            cout << "Invalid input" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        } else if (cin.peek() != '\n') {
            cout << "Enter single word" << endl;
            cin.ignore(10000, '\n');
        } else {
            bool isGood = true;
            if (code == "name") {
                for (auto &item: new_string) {
                    if (!islower(item) && !isupper(item)) {
                        cout << "Use only letters!" << endl;
                        cin.ignore(10000, '\n');
                        isGood = false;
                        break;
                    }
                }
            }
            if (isGood) {
                break;
            }
        }

    }
    return new_string;
}
/*
 * Дополнительное задание:
 * Всё вводится с клавиатуры. Можно будет изменить поле определённого класса. Все переменные подтягиваются с остальных классов. (что?)
 * (т.е. я хочу изменить что-то класса Employee и изменяю там зарплату).
 *
 * Всё с проверками.
 *
 */