#include <stdio.h>

// Из текстового удалить все слова, встречающиеся в бинарном
int main()
{
    FILE *txt, *bin;
    fpos_t posCompareNum = 0;
    int delNum, compareNum, temp;

    txt = fopen("text.txt", "r+");
    bin = fopen("binary.bin", "r+");

    while(1) {
        fread(&delNum, sizeof(int), 1, bin);

        if (feof(bin))
            break;

        rewind(txt);

        while (1) {
            fscanf(txt, "%d", &compareNum);

            if (feof(txt))
                break;

            if (delNum == compareNum) {
                while (1) {
                    fscanf(txt, "%d", &temp);

                    if (feof(txt))
                        break;

                    fsetpos(txt, &posCompareNum);
                    fprintf(txt, "%d", temp);

                    fgetpos(txt, &posCompareNum);
                    fscanf(txt, "%d", &temp);
                }
            }
        }
    }
}