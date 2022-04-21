#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>

// Удалить из бинарного файла числа из диапазона, заданного в командной строке.

// Напонимаю, argc - число переданных параметров в функцию.
// argv - массив строк с, непосредственно, самими параметрами.

int main(int argc, char *argv[])
{
    if(argc < 3)
        return 1;

    char *fileName;
    fileName = strcat(argv[0], ".bin");

    FILE *f = fopen(fileName, "r+b");
    if(f == NULL)
        return 1;

    int numOne, numTwo, numMax, numMin, numToFind, cutSize = 0;

    if(!(numOne = atoi(argv[1])))
        return 1;

    if(!(numTwo = atoi(argv[2])))
        return 1;

    if(numOne > numTwo) {
        numMax = numOne;
        numMin = numTwo;
    }
    else {
        numMax = numTwo;
        numMin = numOne;
    }

    while(1)
    {
        fread(&numToFind, sizeof(int), 1, f);
        if(numToFind == EOF || feof(f))
            break;
        if(numToFind > numMin && numToFind < numMax)
        {
            fseek(f, -sizeof(int), SEEK_CUR);
            fwrite("", 1, 1, f);
            cutSize++;
        }
    }

    chsize(fileno(f), cutSize);
    fclose(f);
}
