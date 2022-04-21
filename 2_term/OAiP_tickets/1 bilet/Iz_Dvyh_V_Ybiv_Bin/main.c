#include <stdio.h>
#include <stdlib.h>

// Два бинарных файла, один отсортиован по возрастанию, второй по убыванию (числа)
// Записать всё в 3 файл, отсортированный по убыванию. Без доп. массивов

int main(void)
{
    int i1, i2;
    fpos_t posF1, posF1_nach;
    FILE *f1, *f2, *f3;

    f1 = fopen("vozr.bin", "rb");
    f2 = fopen("ybiv.bin", "rb");
    f3 = fopen("new.bin", "wb");

    fgetpos(f1, &posF1_nach);

    fseek(f1, -sizeof(int), SEEK_END);

    fgetpos(f1, &posF1);
    fsetpos(f1, &posF1);

    fread(&i1, sizeof(int), 1, f1);
    fread(&i2, sizeof(int), 1, f2);

    do
    {
        if(i2 > i1)
        {
            while(!feof(f2) && i2 > i1)
            {
                fwrite(&i2, sizeof(int), 1, f3);
                fread(&i2, sizeof(int), 1, f2);
            }
            if(feof(f2) && i2 > i1)
            {
                fwrite(&i2, sizeof(int), 1, f3);
                i2 = INT_MAX;
            }
        }
        else
        {
            while(posF1 != posF1_nach && i1 > i2)
            {
                fwrite(&i1, sizeof(int), 1, f3);
                posF1 -= sizeof(int);
                fsetpos(f1, &posF1);
                fread(&i1, sizeof(int), 1, f1);
            }
            if(posF1 == posF1_nach && i1 > i2)
            {
                fwrite(&i1, sizeof(int) ,1, f3);
                i1 = INT_MAX;
            }
        }
    }while(feof(f2) || posF1 != posF1_nach);

    if(i1 != INT_MAX)
        fwrite(&i1, sizeof(int), 1, f3);
    if(i2 != INT_MAX)
        fwrite(&i2, sizeof(int), 1, f3);

    fcloseall();
}

// Вроде все (-_-)
