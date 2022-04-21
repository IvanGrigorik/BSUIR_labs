#include <stdio.h>

// В текстовом файле содержатся двузначные числа.
// Поменять местами первое и последнее, второе и предпоследнее и т.д. числа

int main()
{
    FILE *f = fopen("test.txt", "r+");
    int num1, num2;
    fpos_t pos1 = 0, pos2;

    // Сразу получаем позицию последнего числа в файле
    fseek(f, -2, SEEK_END);
    fgetpos(f, &pos2);
    rewind(f);

    while(pos1 <= pos2)
    {
        fsetpos(f, &pos1);
        fscanf(f, "%d", &num1);

        fsetpos(f, &pos2);
        fscanf(f, "%d", &num2);

        fsetpos(f, &pos2);
        fprintf(f, "%d", num1);

        fsetpos(f, &pos1);
        fprintf(f, "%d", num2);

        fgetpos(f, &pos1);
        pos1 += 1;
        pos2 -= 3;
    }
    fclose(f);
}