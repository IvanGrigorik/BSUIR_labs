#include <stdio.h>
#include <io.h>

// Сортировка бинарного файла методом вставки (Ещё раз, вставка - это когда
// сортируешь по правилу "карт в руке". Идём слева направо и смотрим на элементы сзади

int main()
{
    FILE *binFile;
    fpos_t posSort, posPrev = 0;
    int numSort, numPrev;

    binFile = fopen("new.bin", "r+b");

    fseek(binFile, sizeof(int), SEEK_SET);

    while(1)            // posSort - n1, posPrev - n2.  n3 не используется (-_-)
    {
        fgetpos(binFile, &posSort);
        fread(&numSort, sizeof(int), 1, binFile);

        if(feof(binFile))
            rewind(binFile);

        posPrev = posSort - sizeof(int);

        fsetpos(binFile, &posPrev);

        while(posPrev >= 0)
        {
            fgetpos(binFile, &posPrev);
            fread(&numPrev, sizeof(int), 1, binFile);

            if(numPrev > numSort)
            {
                posPrev += sizeof(int);
                fsetpos(binFile, &posPrev);
                fwrite(&numPrev, sizeof(int), 1, binFile);
                posPrev -= sizeof(int);
            }
            else
                break;

            posPrev -= sizeof(int);

            if(posPrev >= 0)
                fsetpos(binFile, &posPrev);
        }

        posPrev += sizeof(int);
        fsetpos(binFile, &posPrev);
        fwrite(&numSort, sizeof(int), 1, binFile);

        posSort += sizeof(int);

        if(posSort >= filelength(fileno(binFile)))
            break;

        fsetpos(binFile, &posSort);
    }
}
