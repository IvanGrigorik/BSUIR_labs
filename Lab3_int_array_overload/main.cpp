#include <iostream>
#include "Array.h"

int main () {
    Array arr1, arr2, arr3, arr4;

    // Show "()" work
    arr1({7, 7, 7});
    arr2({8, 8, 8});

    // Show "[]" work
    cout << endl << "\"[]\" work:" << endl;
    cout << arr1[2] << endl;

    // Show "++" work
    cout << endl << "\"++\" work: " << endl;
    arr1++;
    cout << arr1 << endl;

    // Show "<" work
    cout << endl << " \"<\" work: " << endl;
    bool dummy_flag = arr1 < arr2;
    cout << dummy_flag << endl;

    // Show "+" work
    cout << endl << "\"+\" work: " << endl;
    arr3 = arr1 + arr2;
    cout << arr3 << endl;

    // Show "=" work
    cout << endl << "\"=\" work: " << endl;
    arr3 = arr1;
    cout << arr3 << endl;

    // Show "--" work
    cout << endl << "\"--\" work: " << endl;
    --arr2;
    cout << arr2 << endl;

    // Show "+" work
    cout << endl << "\"+\" work: " << endl;
    arr3 = arr1 + 10;
    cout << arr3 << endl;

    // Show ">" work
    cout << endl << "\">\" work: " << endl;
    dummy_flag = arr1 > 3;
    cout << dummy_flag << endl;

    // Show "double ()" work
    cout << endl << "\"double ()\" work: " << endl;
    cout << double(arr1) << endl;

    // Show "Array_size" work
    cout << endl << "\"Array_size\" work: " << endl;
    cout << Array_size(arr1) << endl;
    return 0;
}
