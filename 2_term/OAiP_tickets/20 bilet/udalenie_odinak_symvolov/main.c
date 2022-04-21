#include <stdio.h>
#include <io.h>

// Удалить из текстового файла повторяющиеся символы
// По той программе, которая написана, из qqwweeD должно выйти D

int main()
{
    // symbol - буква, которая проверяется на повторяемость.
    char symbol, symbolToCheck, temp;
    fpos_t posSymbol = 0, posSymbolToCheck;

    FILE *f;
    f = fopen("new.txt", "r+");

    int len = filelength(fileno(f)), flag;

    // Проходим по каждой букве в файле, и по числам, которые стоят после него
    while(1)
    {
        flag = 0;
        // Получаем букву, которую будет просматривать на повторяемость
        fgetpos(f, &posSymbol);
        fscanf(f, "%c", &symbol);
        if(feof(f))
            break;

        // Проверяем все буквы, стоящие за буквой для проверки
        while(1)
        {
            fgetpos(f, &posSymbolToCheck);
            fscanf(f, "%c", &symbolToCheck);

            if(feof(f))
                break;

            // Если найдена буква, которая подходит, то..
            if(symbol == symbolToCheck)                 // 12419 <- по этому набору по логике всё должно работать
            {
                flag = 1;
                // Ставим на её место следующую, а на место следующей послеследующую и т.д.
                while(1)
                {
                    fscanf(f, "%c", &temp);
                    if(feof(f))
                    {
                        len -= 1;
                        chsize(fileno(f), len);
                        break;
                    }
                    fseek(f, -2, SEEK_CUR);
                    fprintf(f, "%c", temp);
                    fseek(f, +1, SEEK_CUR);
                }

                // И в конце концов возвращаемся а позицию той буквы, которую проверяли
                // потому что могут стоять несколько одинаковых букв подряд
                fsetpos(f, &posSymbolToCheck);
            }
        }

        if(flag == 1)
        {
            fsetpos(f, &posSymbol);
            fscanf(f, "%c", &temp);
            while(1) {
                fscanf(f, "%c", &temp);
                if(feof(f))
                {
                    len -= 1;
                    chsize(fileno(f), len);
                    break;
                }
                fseek(f, -2, SEEK_CUR);
                fprintf(f, "%c", temp);
                fseek(f, +1, SEEK_CUR);
            }
            posSymbol -= 1;
        }

        // Перемещаемся на следующую позицию для проверки
        posSymbol += 1;
        fsetpos(f, &posSymbol);
    }
}