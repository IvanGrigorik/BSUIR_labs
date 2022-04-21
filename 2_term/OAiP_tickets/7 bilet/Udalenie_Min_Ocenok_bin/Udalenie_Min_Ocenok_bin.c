#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*struct pupil
{
    char *lastName;
    int first, second, third;
};*/

int main(int argc, char *argv[])
{
    char *fileName, temp = 'a', *toDel = "";
    int v1, v2, v3, sum, minSum = INT_MAX;
    FILE *f;
    fpos_t delPoseFirst, delPoseEnd;

    if(argc != 2)
        return 1;

    fileName = strcat(argv[1], ".bin");
    f = fopen(fileName, "w+b");

    while (1)
    {
        while (1)
        {
            /*
             * Если в структуре lastName - строка фиксированной длинны,
             * то можно использовать следующий способ для получения "оценок":
             *
             *   fread(&temp, sizeof(struct pupil), 1, f);
             *   if (feof(f))
             *      break;
             * Таким образом мы перейдём на конец записи, а после этого надо сделать:
             *   fseek(f, -(3*sizeof(int)), SEEK_CUR);
             *
             * Таким образом мы стоим на начале записи "оценок"
             *
             * По такой же логике можно "вырезать" из файла
             */

            fread(&temp, sizeof(char), 1, f);
            if (feof(f) || (temp > '0' && temp < '9')) {
                fseek(f, -1, SEEK_CUR);
                break;
            }
        }
        if (feof(f))
            break;

        // Ищем минимальные оценки
        fread(&v1, sizeof(int), 1, f);
        fread(&v2, sizeof(int), 1, f);
        fread(&v3, sizeof(int), 1, f);
        sum = v1 + v2 + v3;
        if(sum < minSum)
            minSum = sum;
    }

    rewind(f);

    while(1)
    {
        fgetpos(f, &delPoseFirst);
        while(1)
        {
            fread(&temp, sizeof(char), 1, f);
            if (feof(f) || (temp > '0' && temp < '9')){
                fseek(f, -1, SEEK_CUR);
                break;
            }
        }
        if(feof(f))
            break;

        fread(&v1, sizeof(int), 1, f);
        fread(&v2, sizeof(int), 1, f);
        fread(&v3, sizeof(int), 1, f);
        fgetpos(f, &delPoseEnd);

        sum = v1 + v2 + v3;

        if(sum == minSum)
        {
            fsetpos(f, &delPoseFirst);
            while(delPoseFirst != delPoseEnd)
            {
                fwrite(&toDel,1,1, f);
                delPoseFirst++;
            }
        }
    }
    fclose(f);
}