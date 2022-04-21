#include <stdio.h>

/* "�������������" ����, �.�. �������� ������� ������ � ��������� �����, ������ � ������������� � �.�. */

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

    // ������� ��������� � ������
    fpos_t a[2] = {0, 0};

    // ������� ��������� � �����
    fseek(fptr, 0, SEEK_END);
    fpos_t b[2] = {0, 0};
    fgetpos(fptr, &b[0]);
    --b[0];

    char tmp;

    while (a[0] < b[1] && !feof(fptr)) {

        fsetpos(fptr, &a[1]);

        // ��������� ������ ������� �����

        do {
            tmp = fgetc(fptr);
        } while (tmp == ' ' && !feof(fptr));

        if (feof(fptr))
            break;

        fgetpos(fptr, &a[0]);
        --a[0];

        // ��������� ����� ������� �����
        do {
            tmp = fgetc(fptr);
        } while (tmp != ' ' && feof(fptr));

        fgetpos(fptr, &a[1]);
        --a[1];


        // ������� �� ����� ������� �����
        fsetpos(fptr, &b[0]);

        // ��������� ����� ������� �����
        do {
            tmp = fgetc(fptr);
            fseek(fptr, -2, SEEK_CUR);
        } while (tmp == ' ');

        fgetpos(fptr, &b[0]);
        --b[0];

        // ��������� ������ ������� �����
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
        // ���������� � ������ ����� � ������
        fsetpos(fptr, &a[1]);

        // ��������� ����, ���� �� ������������ ������
        do {
            tmp = fgetc(fptr);
        } while (tmp == ' ' && !feof(fptr));

        if (feof(fptr))
            break;

        // �������� ������� ����� ����� � ������ (������� ����� ������ ������)
        fgetpos(fptr, &a[0]); --a[0];

        // ���� ����� ������� �����
        do {
            tmp = fgetc(fptr);
        } while (tmp != ' ' && !feof(fptr));

        if (feof(fptr))
            break;

        // �������� ������� ��������� ����� ������� � ������ �����
        fgetpos(fptr, &a[1]); a[1] -= 2;

        // ��������������� �� ��������� ����� � ����� (� ����� �������� ����� � ������)
        fsetpos(fptr, &b[0]);

        // ���� ����� ������� �����
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
