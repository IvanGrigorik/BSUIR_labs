#include <stdio.h>
#include <stdlib.h>

// ƒаны два бинарных файла, один по возрастанию, второй по убыванию (числа).
// ќтсортировать в третий по возрастанию без доп. массивов

int main(void)
{
    int i1, i2;
    fpos_t /* *posF1 = 0,*/ *posF2 = 0;
    FILE *f1, *f2, *f3;

    f1 = fopen("vozr.bin", "rb");
    f2 = fopen("ybiv.bin", "rb");
    f3 = fopen("new.bin", "w+b");

    // ѕолучаем первое значение из возрастающего файла и последнее из убывающего
    fread(&i1, sizeof(int),1, f1);
    fseek(f2, -sizeof(int), SEEK_END);

    fgetpos(f2, posF2);
    fsetpos(f2, posF2);

    fread(&i2, sizeof(int), 1, f2);

    do
    {
        if(i1 < i2)
        {
            while(!feof(f1) && i1 < i2)
            {
                fwrite(&i1, sizeof(int), 1, f3);
                fread(&i1, sizeof(int), 1, f1);
            }
            if(feof(f1) && i1 < i2) // ≈сли конец файла, то из 34 строки следует, что мы сравниваем конец с i2?
            {
                fwrite(&i1, sizeof(int), 1, f3);
                i1 = INT_MAX;
            }
        }
        else
        {
            while(*posF2 != 0 && i1 >= i2)
            {
                fwrite(&i2, sizeof(int), 1, f3);
                *posF2 -= sizeof(int);
                fsetpos(f2, posF2);
                fread(&i2, sizeof(int), 1, f2);
            }
            if(*posF2 == 0 && i1 >= i2)
            {
                fwrite(&i2, sizeof(int), 1, f3);
                i2 = INT_MAX;
            }
        }
    }while(!feof(f1) || *posF2 != 0);

    if(i1 != INT_MAX)
        fwrite(&i1, sizeof(int), 1, f3);
    if(i2 != INT_MAX)
        fwrite(&i2, sizeof(int), 1, f3);
    fcloseall();
}
