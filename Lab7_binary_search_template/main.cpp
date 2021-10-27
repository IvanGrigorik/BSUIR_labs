#include "binary_find.h"

int main () {

    const int SIZE = 10;
    int array_i[SIZE]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    bin_find<int, SIZE>(array_i, 5);

    double array_d[SIZE]{80.4, 90.2, 100.4, 124.4, 124.5, 125., 125.5, 132.2, 133., 144.8};
    bin_find<double, SIZE>(array_d, 124.5);

//    char array_c[SIZE]{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
//    bin_find<char, SIZE>(array_c, 'E');

    char *str[SIZE + 1]{"A", "AB", "ABC", "ABCD", "ABCDE", "ABCDEF", "ABCCDEFG", "ABCDEFGH", "ABCDEFGHI",
                        "ABCDEFGHIJ"};

    char key[]{"ABC"};

    bin_find<SIZE>(str, key);
}
