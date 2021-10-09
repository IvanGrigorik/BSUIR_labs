#include <iostream>
#include "Cheese.h"
#include "Ceramic_products.h"

int main () {

    Product *ptr[2];


    ptr[0] = new Cheese{12, 10, 123, "Alps"};
    cout << endl << "ptr[0]:" << endl;
    ptr[0]->show();

    ptr[1] = new Ceramic_products{322, 10, "Alps_Fabric"};
    cout << endl << "ptr[1]: " << endl;
    ptr[1]->show();

    // Redefinition work
    ptr[0] = new Ceramic_products{1337, 20, "Alps_another_firm"};
    cout << endl << "ptr[0]: " << endl;
    ptr[0]->show();

    cout << endl << endl << "ptr[0] destructor: " << endl;
    delete ptr[0];

    cout << endl << endl << endl << "ptr[1] destructor: " << endl;
    delete ptr[1];

    system("pause>0");

    return 0;
}

// String input check (code mean what we want to enter)
//string input_string (const string &code) {
//    string new_string;
//    while (true) {
//        cin >> new_string;
//        if (cin.fail() || cin.bad()) {
//            cout << "Invalid input" << endl;
//            cin.clear();
//            cin.ignore(10000, '\n');
//        } else if (cin.peek() != '\n') {
//            cout << "Enter single word" << endl;
//            cin.ignore(10000, '\n');
//        } else {
//            bool isGood = true;
//            if (code == "name") {
//                for (auto &item: new_string) {
//                    if (!islower(item) && !isupper(item)) {
//                        cout << "Use only letters!" << endl;
//                        cin.ignore(10000, '\n');
//                        isGood = false;
//                        break;
//                    }
//                }
//            }
//            if (isGood) {
//                break;
//            }
//        }
//
//    }
//    return new_string;
//}