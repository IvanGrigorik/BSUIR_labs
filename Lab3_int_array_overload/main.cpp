#include <iostream>
#include "Array.h"

int main() {
//    int ARR_SIZE_ = 2;
//
//    int *arr1;
//    arr1 = new int [ARR_SIZE_];
//    arr1[0] = 1;
//    arr1[1] = 2;
//    int *temp_arr = arr1;
//    arr1 = (int*)realloc(arr1, 3);
//    arr1[2] = 3;
//    cout << arr1[0] << " "<< arr1[1] << " " << arr1[2];

    Array arr1;
    arr1({1, 2, 3});
    cout << arr1;
    cout << arr1;
    --arr1;
    cout << arr1;
    cout << (arr1 < 1 ? "true" : "false") << endl;
    arr1++;
    cout << arr1;

    Array arr2;

    arr1 = arr1 + arr2;

    arr2({5, 6, 7});
    arr1 + arr2;
    cout << arr1;
    return 0;
}
