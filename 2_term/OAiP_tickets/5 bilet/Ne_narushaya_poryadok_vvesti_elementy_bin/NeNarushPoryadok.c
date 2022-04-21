#include <stdio.h>

// Не нарушая порядок ввксти в бинарный файл, отсортированный по возрастанию, числа.
int main()
{
    FILE *f;
    f = fopen("new.bin", "w+b");
//
//    int mas[] = {1, 2, 3, 5};
//
//    for(int i = 0; i < 4; i++)
//        fwrite(&mas[i], sizeof(int), 1, f);

    int temp, num, numToCheck;

    fpos_t /*posTemp,*/ posToSwap, posPrevTemp;

    while(1)
    {
        scanf("%d", &num);
        if(num == -1)
            break;

        rewind(f);

        while(1)
        {
            fgetpos(f, &posToSwap);
            fread(&numToCheck, sizeof(int), 1, f);
            if(numToCheck >= num || feof(f))
                break;
        }
        if(feof(f) && num > numToCheck)
        {
            fseek(f, 0, SEEK_END);
            fwrite(&num, sizeof(int), 1, f);
            continue;
        }

        fseek(f, -sizeof(int), SEEK_END);

        do
        {
            fgetpos(f, &posTemp);
            posPrevTemp = posTemp - sizeof(int);
            fread(&temp, sizeof(int), 1, f);

            posTemp += 2*sizeof(int);
            fsetpos(f, &posTemp);

            fwrite(&temp, sizeof(int), 1, f);

            posTemp -= 3*sizeof(int);

            fsetpos(f, &posTemp);

        }while(posTemp != posToSwap);

        fsetpos(f, &posToSwap);
        fwrite(&num, sizeof(int), 1, f);
    }
    fclose(f);
}
