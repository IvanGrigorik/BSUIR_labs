#include <stdio.h>

// Даны файла, отсортированных по возрастанию
// Создать один, отсортированный по убыванию
// Все файлы бинарные

int main() {
    // f1, f2 - возрастающие
    // f3 - новый убывающий
    FILE *f1, *f2, *f3;

    f1 = fopen("file1.bin", "r+");
    f2 = fopen("file2,bin", "r+");
    f3 = fopen("new.bin", "w+");

    fpos_t posF1, posF2;
    int num1, num2;

    fseek(f1, -sizeof(int), SEEK_END);
    fgetpos(f1, &posF1);

    fseek(f2, -sizeof(int), SEEK_END);
    fgetpos(f2, &posF2);


    // Цикл для записи в третий файл,
    // пока не закончится один из файлов
    // (пока не дойдём до начала).
    do {
        fsetpos(f1, &posF1);
        fsetpos(f2, &posF2);
        fread(&num2, sizeof(int), 1, f2);
        fread(&num1, sizeof(int), 1, f1);

        if (num1 > num2)
            fwrite(&num2, sizeof(int), 1, f3);
        else
            fwrite(&num1, sizeof(int), 1, f3);

        posF1 -= sizeof(int);
        posF2 -= sizeof(int);
    } while (posF2 != 0 || posF1 != 0 || posF2 > 0 || posF1 > 0);

    // Если первый файл закончился, а второй нет
    if (posF1 <= 0 && posF2 > 0)
    {
        do
        {
            fsetpos(f2, &posF2);
            fread(&num2, sizeof(int), 1, f2);
            fwrite(&num2, sizeof(int), 1, f3);
            posF2 -= sizeof(int);
        }while(posF2 >= 0);
        return 0;
    }
    else if(posF2 <=0 && posF1 > 0)
    {
        do
        {
            fsetpos(f1, &posF1);
            fread(&num1, sizeof(int), 1, f1);
            fwrite(&num1, sizeof(int), 1, f3);
            posF1 -= sizeof(int);
        }while(posF1 >= 0);
        return 0;
    }
    return 0;
}