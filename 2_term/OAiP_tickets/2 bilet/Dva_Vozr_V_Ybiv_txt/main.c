#include <stdio.h>
#include <stdlib.h>

// Дано два текстовых файла по возрастанию (числа)
// Переписать в третий по убыванию.

int main()
{
    int i1, i2;
    FILE *f1, *f2, *f3;
    fpos_t pos1, pos2;

    f1 = fopen("vozr1.txt", "r");
    f2 = fopen("vozr2.txt", "r");
    f3 = fopen("ybiv.txt", "w");

    fseek(f1, -sizeof(int), SEEK_END);
    fgetpos(f1, &pos1);
    fseek(f2, -sizeof(int), SEEK_END);
    fgetpos(f2, &pos2);

    fscanf(f1, "%d", &i1);
    fscanf(f2, "%d", &i2);

    do
    {
        if(i1 > i2)
        {
            while (pos1 != 0 && i1 > i2)
            {
                fprintf(f3, "%d", i1);
                pos1 -= sizeof(int);
                fsetpos(f1, &pos1);
                fscanf(f1, "%d", &i1);
            }
            if (pos1 == 0)
                i1 = INT_MAX;
        }
        else
        {
            while(pos2 != 0 && i2 > i1)
            {
                fprintf(f3, "%d", i2);
                pos2 -= sizeof(int);
                fsetpos(f2, &pos2);
                fscanf(f1, "%d", &i2);
            }
            if(pos2 == 0)
                i2 = INT_MAX;
        }
    }while(pos1 != 0 || pos2 != 0);

    if(i1 != INT_MAX)
        fprintf(f3, "%d", i1);
    if(i2 != INT_MAX)
        fprintf(f3, "%d", i2);

}
