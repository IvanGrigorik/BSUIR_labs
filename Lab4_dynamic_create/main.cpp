#include <iostream>
#include "Matrix.h"

int main () {
    auto *m1 = new Matrix{
            {
                    {9, 43, 7},
                    {6, 12, 4},
                    {3, 28, 1}
            }
    };

    auto *m2 = new Matrix{*m1};

    cout << "Matrix m1 before sort: " << endl << (*m1);
    cout << "Matrix m2: " << endl << (*m2) << endl << endl;
    m1->sort_selection();
    cout << "Matrix m1 after sort: " << endl << (*m1);
    cout << "Matrix m2 after m1 sort: " << endl << (*m2);

    cout  << endl << "Matrix m1 bin output: " << endl;
    m1->bin_output();

    cout << endl << "Matrix m2 hex output: " << endl;
    m2->hex_output();

    cout << endl << "m1 + m2 dec output: " << endl;
    cout << (*m1) + (*m2);

    cout << endl << "m1 + m2 oct output: " << endl;


    ((*m1) + (*m2)).oct_output();
    system("pause > 0");

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
/*
 * Программа первую матрицу после сортировки выводит в двоичном коде
 * Вторую в шестнадцатеричной (после сортировки первой матрицы)
 *
 * И выводит их сумму в восьмеричной
 *
 */
