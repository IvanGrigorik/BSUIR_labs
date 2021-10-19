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