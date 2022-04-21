#include <io.h>

/*
 * Элемент однонаправленного кольца - структура.
 * Отсортировать кольцо вставкой по названию структур (колода карт).
 */

typedef struct name
{
    char *str;
}name;

typedef struct ring
{
    name structName;
    struct ring *next;
}ring;


// kk – sort
// j – preSort
// g – preCheck
// t – check
//
// Первая итерация в сортировке
//      1              2             7              6              5
//     /\             /\            /\                            /\
//  checkElement  sortElement                               preCheckElement/preSortElement


void sort(ring **enter)
{
    ring *preSort, *sort, *preCheck, *check;
    check = preCheck = *enter;

    while (preCheck->next != *enter)
        preCheck = preCheck->next;

    while(1)
    {
        preSort = preCheck;
        sort = check->next;

        // Ищем элемент, который будет меньше, чем сортируемый
        while (strcmp(preSort->next->structName.str, sort->structName.str) < 0)
            preSort = preSort->next;

        if (sort != preCheck)
        {
            if (preSort != check) {
                check->next = sort->next;
                sort->next = preSort->next;
                preSort->next = sort;
                if (sort->next == *enter)
                    *enter = sort;
            } else
                check = check->next;
        }

        else
        {
            if (sort == preSort)
                *enter = sort;
            else
            {
                check->next = sort->next;
                sort->next = preSort->next;
                preSort->next = sort;
            }
            break;
        }
    }


}