#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"

void enterTextFile(FILE* textFile, char *fileName)
{
    system("cls");

    if(!(textFile = fopen(fileName, "w+")))
        return;

    int  number, much;

    printf("Enter how much number's you want to enter\n>>> ");
    much = check();

    for(int i = 0; i < much; i++)
    {
        printf("Enter %d number: ", i+1);
        number = check();
        fprintf(textFile, "%10d ", number);
    }
    system("cls");
    fclose(textFile);
}

void enterBinaryFile(FILE *binaryFile, char *fileName)
{
    system("cls");
    int much, number;

    if(!(binaryFile = fopen(fileName, "w+b")))
        return;

    printf("\nEnter how much elements you want to enter\n>>> ");
    much = check();

    system("cls");

    printf("\nEnter file information\n");
    for(int i = 0; i < much; i++)
    {
        printf("Enter %d number: ", i+1);
        number = check();
        fwrite(&number, sizeof(int), 1, binaryFile);
    }
    fclose(binaryFile);
    system("cls");
}

void outputBinary(FILE *binaryFile, char *fileName)
{
    system("cls");
    if(!(binaryFile = fopen(fileName, "r+b")))
        return;

    int number;
    printf("\nYour value's: ");
    while(1)
    {
        fread(&number, sizeof(int), 1, binaryFile);
        if(feof(binaryFile))
            break;
        printf("%d ", number);
    }
    system("pause>0");
    system("cls");

    fclose(binaryFile);
}

void oneElement(FILE *binaryFile, char *fileName)
{
    system("cls");
    if(!(binaryFile = fopen(fileName, "r+b")))
        return;

    int number, numberToFind, rest;
    int counter = 0;
    printf("\nEnter element to find\n>>> ");
    numberToFind = check();

    while(1)
    {
        if(fread(&number, sizeof(int), 1, binaryFile) != 1)
            break;

        do
        {
            rest = number % 10;
            if(rest == numberToFind)
                counter++;
            number /= 10;
        }while(number);

    }
    system("cls");
    printf("\nNumber %d occurs %d times in the file\n", numberToFind, counter);

    system("pause>0");
    system("cls");

    fclose(binaryFile);
}

void swapElements(FILE *binaryFile, char *fileName)
{
    system("cls");
    if(!(binaryFile = fopen(fileName, "r+b")))
        return;

    int numberToSwap, numMax = 0, temp = 0;
    printf("Enter element to swap\n>>> ");
    numberToSwap = check();

    fseek(binaryFile, 0, SEEK_SET);
    fpos_t prevPos, nextPos;

    while(1)
    {
        fread(&temp, sizeof(int), 1, binaryFile);
        if(feof(binaryFile))
            break;
        if(numMax < temp)
            numMax = temp;
    }

    fseek(binaryFile, 0, SEEK_SET);
    fgetpos(binaryFile, &prevPos);

    while(1)
    {
        fgetpos(binaryFile, &nextPos);
        fread(&temp, sizeof(int), 1, binaryFile);
        if(feof(binaryFile))
            break;
        if(temp == numberToSwap)
        {
            fsetpos(binaryFile, &prevPos);
            fwrite(&numMax, sizeof(int), 1, binaryFile);
            fsetpos(binaryFile, &nextPos);
        }
        fgetpos(binaryFile, &prevPos);
    }

    system("cls");
    fclose(binaryFile);
}

void outputText(FILE *textFile, char *fileName)
{
    system("cls");
    if(!(textFile = fopen(fileName, "r+")))
        return;

    int k;
    printf("Your value's: ");
    while(1)
    {
        fscanf(textFile, "%d", &k);
        if(feof(textFile))
            break;
        printf("%d ", k);
    }

    system("pause>0");
    system("cls");

    fclose(textFile);
}

void occurText(FILE *textFile, char *fileName)
{
    system("cls");
    int symbolToFind, symbolToCheck, i=0;

    if(!(textFile = fopen(fileName, "r+")))
        return;

    printf("\nEnter 1 element to check occur\n>>> ");
    rewind(stdin);
    scanf("%d", &symbolToFind);

    while(1)
    {
        fscanf(textFile, "%d", &symbolToCheck);
        if(feof(textFile))
            break;
        if(symbolToCheck == symbolToFind)
            i++;
    }
    system("cls");
    printf("Number \"%d\" occur %d time's", symbolToFind, i);
    system("pause>0");
    system("cls");
    fclose(textFile);
}

void move(FILE *textFile, char *fileName)
{
    system("cls");

    if(!(textFile = fopen(fileName, "r+")))
        return;

    int moveNum, number, nextNumber;

    printf("\nEnter how much to shift the numbers\n>>> ");
    do
    {
        moveNum = check();
        if(moveNum < 0 || moveNum > 1000)
        {
            system("cls");
            printf("Enter right number to shift\n>>> ");
        }
    }while(moveNum < 0 || moveNum > 1000);

    rewind(textFile);
    for(; moveNum; moveNum--)                       /// 1 2 3
    {
        fscanf(textFile, "%10d", &number);
        while(1)
        {
            if(fscanf(textFile, "%10d", &nextNumber) == EOF)
            {
                rewind(textFile);
                fprintf(textFile, "%10d", number);
                break;
            }
            fseek(textFile, -10, SEEK_CUR);
            fprintf(textFile, "%10d", number);
            number = nextNumber;
            fseek(textFile, 0, SEEK_CUR);
        }
        rewind(textFile);
    }
    fclose(textFile);
    system("cls");
}

int menuText()
{
    puts("Enter:");
    puts("1 - to enter information into a file");
    puts("2 - to output information from a file");
    puts("3 - to determine how many times number occurs");
    puts("4 - to shift the file to the right");
    printf("0 - to end close program\n>>> ");
    int x = check();
    return x;
}

int menuBin()
{
    puts("Enter:");
    puts("1 - to enter information into a file");
    puts("2 - to output information from a file");
    puts("3 - to determine how many times number occurs");
    puts("4 - to replace all max number's");
    printf("0 - to end close program\n>>> ");
    int x = check();
    return x;
}

char *getFileName(int code)
{
    char c;
    char *temp = NULL;
    int k;
    rewind(stdin);

    for(k = 0; (c = (char)getchar()) != '\n'; k++)
    {
        if((c < 'A' || c > 'Z') && (c < 'a' || c > 'z') && (c < '0' || c > '9'))
        {
            puts("\nPlease, enter right format");
            puts("Press any button to continue");
            system("pause > 0");
            rewind(stdin);
            return NULL;
        }

        if (!(temp = (char*)realloc(temp, (k + 6) * sizeof(char))))
        {
            puts("Retry enter\n");
            return NULL;
        }
        temp[k] = c;
    }
    if(code == 1)
    {
        temp[k] = '.';
        temp[k+1] = 't';
        temp[k+2] = 'x';
        temp[k+3] = 't';
        temp[k+4] = '\0';
    }
    if(code == 2)
    {
        temp[k] = '.';
        temp[k+1] = 'b';
        temp[k+2] = 'i';
        temp[k+3] = 'n';
        temp[k+4] = '\0';
    }

    return temp;
}

int check()
{
    char y;
    int x;
    while ((scanf("%d%c", &x, &y)) != 2 || y != '\n')
    {
        rewind(stdin);
        system("cls");
        puts("Please, enter correct format: ");
    }
    return x;
}

char *MyItoA(int num)
{
	int sum = num;
	int i = 0;
	int digit;
	char *str = (char*)malloc(12);

	do
	{
		digit = sum % 10;
		if (digit < 10)
			str[i++] = '0' + digit;
		sum /= 10;
	}while (sum && str[i-1]);

	str[i] = '\0';
	strrev(str);
	return str;
}
