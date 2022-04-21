#include <stdio.h>
#include <stdlib.h>

// Поменять в бинарном файле местами 1 и 2 элемнт, 2 и 3 и т.д.

int main()
{
    FILE *f;

    f = fopen("new.bin", "r+");
    int temp1, temp2;
    fpos_t n1 = 0;

    while(!feof(f))
    {
        fsetpos(f, &n1);

        fread(&temp1, sizeof(int), 1, f);
        if(feof(f) || temp1 == EOF)
            break;

        fread(&temp2, sizeof(int), 1, f);
        if(feof(f) || temp1 == EOF)
            break;

        fsetpos(f, &n1);

        fwrite(&temp2, sizeof(int), 1, f);
        fwrite(&temp1, sizeof(int), 1, f);

        n1 += 2;
    }
    system("pause");
}