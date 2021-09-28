#include <iostream>
#include "Matrix.h"

int main () {
    auto *m1 = new Matrix{
            {
                    {9, 43, 7},
                    {6, 12, 4},
                    {3, 23, 1}
            }
    };

    auto *m2 = new Matrix{*m1};

    cout << "Matrix m1 before sort: " << endl << (*m1);
    cout << "Matrix m2: " << endl << (*m2) << endl << endl;
    m1->sort_selection();
    cout << "Matrix m1 after sort: " << endl << (*m1);
    cout << "Matrix m2 after m1 sort: " << endl << (*m2);
}

/* Another way
   Matrix m1{
            {
                    {9, 8, 7},
                    {6, 23, 4},
                    {3, 2, 1}
            }
    };

    Matrix m2{m1};

    cout << "Matrix m1 before sort: " << endl << m1;
    cout << "Matrix m2: " << endl << m2 << endl << endl;
    m1.sort_selection();
    cout << "Matrix m1 after sort: " << endl << m1;
    cout << "Matrix m2 after m1 sort: " << endl << m2;
*/