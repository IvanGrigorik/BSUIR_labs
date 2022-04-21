#include <stdio.h>

// Дан отсортированный текстовый файл
// Написать программу для добавления символа, не нарушая упорядоченность.
// Примем, что файл отсортирован по возрастанию

int main()
{
    FILE *f = fopen("text.txt", "r+");
    fpos_t newSymbolPos, tempPos;
    char newSymbol, checkSymbol, temp;

    scanf("%c", &newSymbol);

    // Поиск места под символ
    while(1)
    {
        fgetpos(f, &newSymbolPos);
        fscanf(f, "%c", &checkSymbol);
        if(newSymbol < checkSymbol || feof(f))
            break;
    }

    // Если все символы меньше, чем наш, то вставляем в конец
    // ----------Даже на этом этапе работает криво-----------
    if(feof(f))
    {
        fprintf(f, "%c", newSymbol);
        return 0;
    }

    fseek(f, -1, SEEK_END);
    fgetpos(f, &tempPos);

    // Освобождение новой позиции под символ
    do
    {
        fscanf(f, "%c", &temp);
        fseek(f, 0 , SEEK_CUR);
        fprintf(f, "%c", temp);
        --tempPos;
        fsetpos(f, &tempPos);
    }while(tempPos >= newSymbolPos);

    fsetpos(f, &newSymbolPos);
    fprintf(f, "%c", newSymbol);
}