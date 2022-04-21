#include <stdio.h>
#include <io.h>

// Билет 3
// Осуществить сортировку текстового файла методом отбора и вставок
// Принимаем длинну числа как 4 байта (размер инта). (можно оптимизировать можно нет, хз)

void sortVstavka(FILE *F);
void sortOtbot(FILE *F);

int main(void)
{
    FILE *F;

    int mas[] = {111, 888, 666, 111, 222, 555, 111, 222};

    F = fopen("new.txt", "w+");
    for(int i = 0; i < 8; i++)
        fprintf(F, "%d ", mas[i]);

    rewind(F);

    // Вставкой
    sortVstavka(F);

    // Отбором
    sortOtbot(F);

    fclose(F);
}

// Суть сортировки - смотрим на первый элемент и на все, стоящие после него,
// ищем минимальный  и меняем местами (свапаем), потом переходим на второй и смотрим на него,
// ищем минимальный относительно его и свапаем, и т.д. Отбор - потому что потому что отбираем минимальный элемент.
// Отбор - идём справа налево
//
//  8  10 1 13
//  /\ /\
//   |_|     8 < 10, минимальный элемент всё ещё пока 8
//
//  8  10 1 13
//  /\    /\
//   |____| Минимальный элемент уже 1
//
//  8  10 1 13
//  /\      /\
//   |______| Минимальный элемент всё ещё 1 и EOF
//
// Свапаем 1 и 8 местами
//
//  1 10 8 13
// Проделываем ту же процедуру для 10 и тд

void sortOtbot(FILE *F)
{
    int minElement, sortElement, nextElement;
    fpos_t posSortElement, posMinElement, posNext;

    while(1)
    {
        fgetpos(F, &posSortElement);
        fscanf(F, "%d", &sortElement);

        if(feof(F))
            break;

        minElement = sortElement;
        posMinElement = posSortElement;

        while(1)
        {
            fgetpos(F, &posNext);
            fscanf(F, "%d", &nextElement);

            if(nextElement < minElement)
            {
                minElement = nextElement;
                posMinElement = posNext;
            }

            if(feof(F))
                break;
        }

        if(posMinElement != posSortElement)
        {
            fsetpos(F, &posSortElement);
            fprintf(F, "%d", minElement);
            fsetpos(F, &posMinElement);
            fprintf(F, "%d", sortElement);
        }
        posSortElement += sizeof(int);
        fsetpos(F, &posSortElement);
    }
}

// Суть сортировки - сравниваем со второго элемента те элементы позади и так идём до конца.
// Как с колодой карт (смотрим сначала на первую карту, потом на вторую, и сравниваем её с первой,
// если надо - перемещаем, потом на третью и сравниваем с первой и второй и т.д.). Вставка - потому что извлекаем неотсорированный элемент и вставляем его на своё место

//  8  10 1 13
//  /\ /\
//   |_|     10 > 18, всё ок, идём дальше
//
//  8  10 1 13
//     /\ /\
//      |_| 1 < 10, делаем свап.
//
//  8  1 10 13
//  /\ /\
//   |_| 1 < 8, делаем свап.

//  1  8 10 13

void sortVstavka(FILE *F)
{
    int numToSort, prevNum;
    fpos_t posSortNum, posPrev;

    fseek(F, sizeof(int), SEEK_SET);
    while(1)
    {
        fgetpos(F, &posSortNum);
        fscanf(F, "%d", &numToSort);

        if(feof(F))      // ??
            rewind(F);

        posPrev = posSortNum - sizeof(int);

        fsetpos(F, &posPrev);

        while(posPrev >= 0)
        {
            fgetpos(F, &posPrev);
            fscanf(F, "%d", &prevNum);

            if(prevNum > numToSort)
            {
                posPrev += sizeof(int);
                fsetpos(F, &posPrev);
                fprintf(F, "%d", prevNum);
                posPrev -= sizeof(int);
            }
            else
                break;
            posPrev -= sizeof(int);

            if(posPrev >= 0)
                fsetpos(F, &posPrev);
        }

        posPrev += sizeof(int);
        fsetpos(F, &posPrev);
        fprintf(F, "%d", numToSort);

        posSortNum += sizeof(int);
        if(posSortNum >= filelength(fileno(F)))
            break;
        fsetpos(F, &posSortNum);
    }
}
