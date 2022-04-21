#include <stdio.h>
#include <io.h>

// Из бинарного удалить то, что встречается в текстовом
int main()
{
    FILE *binFile, *txtFile;
    int delTxt, compareBin, temp;
    fpos_t posCompare = 0;

    binFile = fopen("new.bin", "w+");
    txtFile = fopen("test.txt", "w+");

    while (1)
    {
        fscanf(txtFile, "%d", &delTxt);

        posCompare = 0;

        while (1)
        {
            fsetpos(binFile, &posCompare);

            fread(&compareBin, sizeof(int), 1, binFile);

            if(feof(binFile))
                break;

            if (compareBin == delTxt)
            {
                while (1)
                {
                    fread(&temp, sizeof(int), 1, binFile);

                    if(feof(binFile))
                        break;

                    fseek(binFile, (-2)*sizeof(int), SEEK_CUR);

                    fwrite(&temp, sizeof(int), 1, binFile);

                    fseek(binFile, sizeof(int), SEEK_CUR);
                }
                chsize(filelength(fileno(binFile)), sizeof(int));
            }
            else
                posCompare += sizeof(int);
        }
        if(feof(txtFile))
            break;
    }
    fcloseall();
}