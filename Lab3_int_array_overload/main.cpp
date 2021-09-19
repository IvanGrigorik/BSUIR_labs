#include <iostream>
#include "Array.h"

int main () {
    Array arr1, arr2;

    // Show "()" work
    arr1({7, 7, 3});
    arr2({8, 8, 8});

    cout << "Arr1: " << arr1  << endl;
    cout << "Arr2: " << arr2;

    // Show "[]" work
    cout << endl << "\"[]\" work:" << endl;
    cout << "arr1[2] = " << arr2[2] << endl;

    // Show "++" work
    cout << endl << "\"++\" double work (in postfix and prefix form): " << endl;
    cout << "Arr2 before incrementing: " << arr2 << endl;
    ++arr2;
    arr2++;
    cout << "Arr2 after incrementing: " << arr2 << endl;

    // Show "<" work
    cout << endl << " \"<\" work: " << endl;
    cout << "Is " << arr1 << " < " << arr2 << "? " << endl << "(0 - false/1 - true): ";
    bool dummy_flag = arr1 < arr2;
    cout << dummy_flag << endl;

    Array arr3;
    // Show "+" work
    cout << endl << "\"+\" work: " << endl;
    cout << arr1 << " + " << arr2 << " = ";
    arr3 = arr1 + arr2;
    cout << arr3 << endl;

    // Show "=" work
    cout << endl << "\"=\" work: " << endl;
    cout << "Arr1: " << arr1 << endl;
    arr3 = arr1;
    cout << "Copied array: " << arr3 << endl;

    // Show "--" work
    cout << endl << "\"--\" double work (in postfix and prefix form): " << endl;
    cout << "Arr2 before decrementing: " << arr2 << endl;
    --arr2;
    arr2--;
    cout << "Arr2 after decrementing: " << arr2 << endl;

    // Show "+" work
    cout << endl << "\"+\" work: " << endl;
    cout << arr1 << " + 10 = ";
    arr3 = arr1 + 10;
    cout << arr3 << endl;

    // Show ">" work
    cout << endl << "\">\" work: " << endl;
    cout << "Is " << arr1 << " > 3 (in power): ";
    dummy_flag = arr1 > 3;
    cout << dummy_flag << endl;

    // Show "double ()" work
    cout << endl << "\"double ()\" work: " << endl;
    cout << arr1 << " average = ";
    cout << static_cast<double>(arr1) << endl;

    // Show "Array_size" work
    cout << endl << "\"Array_size\" work: " << endl;
    cout <<  static_cast<Array_size>(arr1) << endl;
    return 0;
}
