#include "binary_find.h"
#include "menu_func.h"

int main() {


    Array new_arr;

    while (true) {
        switch (get_menu_choice ()) {
            case 1:
                get_array_element (new_arr);
                break;

            case 2:
                show_arr (new_arr);
                break;

            case 3:
                sort (new_arr);
                break;


            case 0:
                exit (EXIT_SUCCESS);

            default:
                exit (EXIT_FAILURE);

        }
    }





/*    const int SIZE = 10;
    int array_i[SIZE]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    bin_find<int, SIZE> (array_i, 5);

    double array_d[SIZE]{80.4, 90.2, 100.4, 124.4, 124.5, 125., 125.5, 132.2, 133., 144.8};
    bin_find<double, SIZE> (array_d, 124.5);
    bin_find<double, SIZE> (array_d, 123);

    char *str[SIZE + 1]{"A", "AB", "ABC", "ABCD", "ABCDE", "ABCDEF", "ABCCDEFG", "ABCDEFGH", "ABCDEFGHI",
                        "ABCDEFGHIJ"};

    bin_find<SIZE> (str, "ABC");*/

    system ("pause>0");
}

// Всё вводим с клавиатуры. Сортировку сделать. Смешанный массив (в массиве могут быть и цифры и буквы).
// P.S. В массиве может быть или как целые слова или как символы, всё зависит от моего выбора.
// Поиск по аски-коду. (теперь вместо ключа передаётся аски-символ элемента).
// З.Ы. "Ввод китайский иероглифов. (Как прикол, не обязательно)."