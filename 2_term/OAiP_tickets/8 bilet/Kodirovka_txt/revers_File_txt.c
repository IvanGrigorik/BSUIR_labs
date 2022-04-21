#include <stdio.h>

/* "Закондировать" файл, т.е. поменять местами первое и последнее слово, второе и предпоследнее и т.д. */

void fptrRev(FILE *fptr, fpos_t a, fpos_t b)
{
    char tmp1, tmp2;

    while (a < b) {
        fsetpos(fptr, &a);
        tmp1 = fgetc(fptr);

        fsetpos(fptr, &b);
        tmp2 = fgetc(fptr);

        fsetpos(fptr, &a);
        fputc(tmp2, fptr);

        fsetpos(fptr, &b);
        fputc(tmp1, fptr);

        ++a, --b;
    }

    return;
}

int main(void) {
    FILE *fptr = fopen("test.txt", "r+");

    // Позиция элементов с начала
    fpos_t a[2] = {0, 0};

    // Позиция элементов с конца
    fseek(fptr, 0, SEEK_END);
    fpos_t b[2] = {0, 0};
    fgetpos(fptr, &b[0]);
    --b[0];

    char tmp;

    while (a[0] < b[1] && !feof(fptr)) {

        fsetpos(fptr, &a[1]);

        // Получение начала первого слова

        do {
            tmp = fgetc(fptr);
        } while (tmp == ' ' && !feof(fptr));

        if (feof(fptr))
            break;

        fgetpos(fptr, &a[0]);
        --a[0];

        // Поулчение конца первого слова
        do {
            tmp = fgetc(fptr);
        } while (tmp != ' ' && feof(fptr));

        fgetpos(fptr, &a[1]);
        --a[1];


        // Переход на конец второго слова
        fsetpos(fptr, &b[0]);

        // Получение конца второго слова
        do {
            tmp = fgetc(fptr);
            fseek(fptr, -2, SEEK_CUR);
        } while (tmp == ' ');

        fgetpos(fptr, &b[0]);
        --b[0];

        // Получение начала второго слова
        do {
            tmp = fgetc(fptr);
            fseek(fptr, -2, SEEK_CUR);
        } while (tmp != ' ');

        fgetpos(fptr, &b[1]);
        ++b[1];

        fptrRev(fptr, a[0], a[1]);
        fptrRev(fptr, b[0] + 1, b[1] + 1);
        fptrRev(fptr, a[0], b[1] + 1);

        ++a[1];
        --b[0];
    }

    fclose(fptr);

    return 0;
}

/*
    while (a[0] < b[0] && !feof(fptr))
    {
        // Становимся в начало слова с начала
        fsetpos(fptr, &a[1]);

        // Выполняем цикл, пока не обнаруживаем пробел
        do {
            tmp = fgetc(fptr);
        } while (tmp == ' ' && !feof(fptr));

        if (feof(fptr))
            break;

        // Получаем позицию конца слова с начала (пробела перед вторым словом)
        fgetpos(fptr, &a[0]); --a[0];

        // Ищем конец второго слова
        do {
            tmp = fgetc(fptr);
        } while (tmp != ' ' && !feof(fptr));

        if (feof(fptr))
            break;

        // Получаем позицию последней буквы второго с начала слова
        fgetpos(fptr, &a[1]); a[1] -= 2;

        // Устанавливаемся на последнюю букву в файле (в файле записано слово и пробел)
        fsetpos(fptr, &b[0]);

        // Ищем конец второго слова
        do {
            tmp = fgetc(fptr);
            fseek(fptr, -2, SEEK_CUR);
        } while(tmp == ' ');

        fgetpos(fptr, &b[1]); ++b[1];

        // one two three four five six seven eight nine ten
        do {
            tmp = fgetc(fptr);
            fseek(fptr, -2, SEEK_CUR);
        } while (tmp != ' ');

        fgetpos(fptr, &b[0]); b[0] += 2;

        fptrRev(fptr, a[0], a[1]);
        fptrRev(fptr, b[0] + 1, b[1] + 1);
        fptrRev(fptr, a[0], b[1] + 1);

        ++a[1], --b[0];
    }

    fclose(fptr);

    return 0;
}
*/
/*

#include <stdio.h>

void fptrrev(FILE *fptr, fpos_t a, fpos_t b)
{
    char tmp[2];

    while (a < b) {
        fsetpos(fptr, &a);
        tmp[0] = fgetc(fptr);

        fsetpos(fptr, &b);
        tmp[1] = fgetc(fptr);

        fsetpos(fptr, &a);
        fputc(tmp[1], fptr);

        fsetpos(fptr, &b);
        fputc(tmp[0], fptr);

        ++a, --b;
    }

    return;
}

int main(void)
{
    FILE *fptr = fopen("test.txt", "r+");

    fpos_t a[2] = { 0, 0 };

    fseek(fptr, 0, SEEK_END);

    fpos_t b[2] = { 0, 0 };
    fgetpos(fptr, &b[0]); --b[0];

    char tmp;

    while (a[0] < b[0] && !feof(fptr)) {
        fsetpos(fptr, &a[1]);

        do {
            tmp = fgetc(fptr);
        } while (tmp == ' ' && !feof(fptr));

        if (feof(fptr))
            break;

        fgetpos(fptr, &a[0]); --a[0];

        do {
            tmp = fgetc(fptr);
        } while (tmp != ' ' && !feof(fptr));

        if (feof(fptr))
            break;

        fgetpos(fptr, &a[1]); a[1] -= 2;

        // =====

        fgetpos(fptr, &b[0]);

        do {
            tmp = fgetc(fptr);
            fseek(fptr, -2, SEEK_CUR);
        } while (tmp == ' ');

        fsetpos(fptr, &b[1]); ++b[1];

        do {
            tmp = fgetc(fptr);
            fseek(fptr, -2, SEEK_CUR);
        } while (tmp != ' ');

        fsetpos(fptr, &b[0]); b[0] += 2;

        fptrrev(fptr, a[0], a[1]);
        fptrrev(fptr, b[0] + 1, b[1] + 1);
        fptrrev(fptr, a[0], b[1] + 1);

        ++a[1], --b[0];
    }

    fclose(fptr);

    return 0;
}*/
