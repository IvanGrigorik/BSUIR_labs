#include <stdio.h>
#include <stdlib.h>
#include <io.h>

// Сортировка двунаправленного кольца методом изменения указателей.
struct ring
{
    char *data;
    struct ring *right;
    struct ring *left;
};

struct ring *sort(struct ring *enter)
{
    struct ring *elementToCompare, *checkElement, *minInRing; // s1, s2, s3
    int i;
    elementToCompare = enter;

    do
    {
        checkElement = elementToCompare->right;                    // Бегунок по кольцу (для поиска минимального значения)
        minInRing = elementToCompare;                              // указатель для запоминания элемента

        do{                                                        // Поиск минимального значения в кольце (с checkElement до enter)
            if(strcmp(checkElement->data, minInRing->data) < 0)    // Если значение в бегунке меньше, чем минимальное до этого,
                minInRing = checkElement;                          // то перезаписываем
            checkElement = checkElement->right;                    // И так обходим всё кольцо
        }while(checkElement != enter);                             // до момента, пока бегунок не дойдёт до начала кольца

        if(minInRing != elementToCompare)                          // Если минимальный элемент оказался не данным (т.е. сработал прошлый цикл)
        {
            if(elementToCompare == enter)
                enter = minInRing;

            minInRing->left->right = minInRing->right;             // Убираем элемент из кольца
            minInRing->right->left = minInRing->left;
                                                                   // Возня с переставлением элемента. Меняем:
            elementToCompare->left->right = minInRing;             // правый указатель предыдущего элемента на новый
            minInRing->right = elementToCompare;                   // правый указатель нового элемента на сравниемый
            minInRing->left = elementToCompare->left;              // левый указатель нового элемента на левый указатель сравниемого
            elementToCompare->left = minInRing;                    // левый указатель сравниемого на новый
        }
        else                                                       // Если минимального элемента не найдено
            elementToCompare = elementToCompare->right;            // то продолжаем цикл
    }while(elementToCompare->right != enter);
    return enter;                                                  // Возвращаем новую точку входа (!!!!!!)
}
