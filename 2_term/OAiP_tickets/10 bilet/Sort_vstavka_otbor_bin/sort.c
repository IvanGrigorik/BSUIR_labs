#include <stdio.h>
#include <io.h>

/*
 * Сортировать бинарный файл методом вставки
 * (смотрим на второй, сравниваем с предыдущим, если надо - заменяем, и т.д.)
 *
 * Сортировать бинарный файл методом отбора
 * (смотрим на первый и ищем меньше его в оставшемся файле, если надо - заменяем)
 *
 */

void vstavka(FILE *f);
void otbor(FILE *f);

int main()
{

    FILE *f;
    f = fopen("new.bin", "r+b");

    vstavka(f);
    otbor(f);

}

void vstavka(FILE *f)
{
    fpos_t posElementToCompare, posCheckPrevElement;
    int elementToCompare, checkPrevElement;

    fseek(f, sizeof(int), SEEK_SET);

    fgetpos(f, &posElementToCompare);

    while (1)
    {
        fsetpos(f, &posElementToCompare);

        fread(&elementToCompare, sizeof(int), 1, f);
        if (feof(f))
            rewind(f);

        posCheckPrevElement = posElementToCompare - sizeof(int);

        while (posCheckPrevElement >= 0)
        {
            fgetpos(f, &posCheckPrevElement);
            fread(&checkPrevElement, sizeof(int), 1, f);

            if (checkPrevElement > elementToCompare)
            {
                posCheckPrevElement += sizeof(int);
                fsetpos(f, &posCheckPrevElement);
                fwrite(&checkPrevElement, sizeof(int), 1, f);
                posCheckPrevElement-=sizeof(int);
            }
            else
                break;

            posCheckPrevElement -= sizeof(int);

            if (posElementToCompare >= 0)
                fsetpos(f, &posCheckPrevElement);
        }

        posElementToCompare += sizeof(int);
        fsetpos(f, &posCheckPrevElement);
        fwrite(&elementToCompare, sizeof(int), 1, f);

        posElementToCompare += sizeof(int);
        if (posElementToCompare >= filelength(fileno(f)))
            break;

        fsetpos(f, &posElementToCompare);
    }
}

void otbor(FILE *f)
{
    int sortElement, minElement, checkElement;
    fpos_t posSortElement = 0, posMinElement = 0, posCheckElement = 1;

    while (1)
    {
        fgetpos(f, &posSortElement);
        fread(&sortElement, sizeof(int), 1, f);

        minElement = sortElement;
        fgetpos(f, &posCheckElement);


        // Поиск минимального элемента в файле после сравниемого
        while (1)
        {
            fgetpos(f, &posCheckElement);
            fread(&checkElement, sizeof(int), 1, f);

            if (feof(f))
                break;

            if (checkElement < minElement) {
                posMinElement = posCheckElement;
                minElement = checkElement;
            }
            ++posCheckElement;
        }

        // Заменяем, если получено новое минимальное значение
        if (minElement != sortElement)
        {
            fsetpos(f, &posMinElement);
            fwrite(&sortElement, sizeof(int), 1, f);
            fsetpos(f, &posSortElement);
            fwrite(&minElement, sizeof(int), 1, f);
        }

        posSortElement++;

        if(posSortElement == filelength(fileno(f)))
            break;

        fsetpos(f, &posSortElement);



        if(feof(f))
            break;
    }
}