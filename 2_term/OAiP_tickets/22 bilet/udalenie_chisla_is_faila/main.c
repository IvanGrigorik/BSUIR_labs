#include <stdio.h>
#include <io.h>

// Организовать ввод числа с клавиатуры
// и его удаление из бинарного файла

int main()
{
    FILE *f = fopen("test.bin", "w+");
    int numToDel, numToCheck, temp;
    scanf("%d", &numToDel);
    fpos_t posToCheck = 0;
    int len = filelength(fileno(f));

    while(1)
    {
        fgetpos(f, &posToCheck);
        fread(&numToCheck, sizeof(int), 1, f);
        if(feof(f))
            break;

        if(numToDel == numToCheck)
        {
            fread(&temp, sizeof(int), 1, f);
            if(feof(f))
            {
                len -= sizeof(int);
                chsize(fileno(f), len);
                break;
            }
            fseek(f, -sizeof(int), SEEK_CUR);

            while(1)
            {                                           // 12349
                fread(&temp, sizeof(int), 1, f);
                if(feof(f))
                {
                    len -= sizeof(int);
                    chsize(fileno(f), len);
                    break;
                }
                // Перемещаемся на позицию позапрошлого числа
                fseek(f,-(sizeof(int)*2), SEEK_CUR);
                fwrite(&temp, sizeof(int), 1, f);
                fseek(f, sizeof(int), SEEK_CUR);
            }
            fsetpos(f, &posToCheck);

            continue;

        }
        posToCheck++;
        fsetpos(f, &posToCheck);
    }
}