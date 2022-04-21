#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functionshead.h"

int menu()
{
    puts("\nEnter: ");
	puts("1) Add tour's");
	puts("2) Show tour's");
	puts("3) Search tour's");
	puts("4) Delete tour's");
	puts("5) Show longest tour");
    puts("0) Close program");
    printf(">>> ");
	int x;
	x = check();
	return x;
}

struct base enter(struct base toursList)
{
    system("cls");
    printf("\nHow much tour's you would enter?\n>>> ");
    int num;
    num = check();
    struct tour *temp;
    toursList.amount += num;
    if (!(temp = (struct tour*)realloc(toursList.tours, toursList.amount * sizeof(struct tour))))
    {
        toursList.amount -= num;
        puts("Not enough memory to add new tour!");
        return toursList;
    }
    toursList.tours = temp;

    static int k = 0;
    int choise;
    system("cls");

    do
    {
        puts("\nWhat do you want to enter?");
        puts("1 - enter by date's");
        puts("2 - enter by duration's");
        printf("0 - to exit\n>>> ");
        choise = check();
        system("cls");
    }while(choise < 0 || choise > 2);

    system("cls");

    switch(choise)
    {
        case 0: return toursList;

        case 1:{
            for(int i = toursList.amount - num; i < toursList.amount; ++i)
            {
                printf("\nTour %d\n", ++k);
                toursList = enterNameCost(i, toursList);
                toursList.tours[i].indicator = 1;
                do
                {
                    printf("Enter date in format ddmmyyyy: ");
                    fflush(stdin);
                }while(!getDigits(i, toursList));
                system("cls");
            }
            break;
        }

        case 2:{
            for(int i = toursList.amount - num; i < toursList.amount; ++i)
            {
                printf("\nTour %d\n", ++k);
                toursList = enterNameCost(i, toursList);
                toursList.tours[i].indicator = 2;
                do
                {
                    printf("Enter duration: ");
                    fflush(stdin);
                }while(!(toursList.tours[i].info.duration = check()));
                system("cls");
            }
            break;
        }
    }

    system("cls");
    return toursList;
}

struct base enterNameCost(int i, struct base toursList)
{
    do
    {
        printf("Enter tour name: ");
        rewind(stdin);
    }while(!(toursList.tours[i].name = getString()));

    do
    {
        printf("Enter cost: ");
        rewind(stdin);
    }while(!(toursList.tours[i].cost = check()));
    return toursList;
}

void output(struct base toursList)
{
    system("cls");
    if (toursList.tours == NULL)
    {
        printf("\nTour's not enrolled\n");
        system("pause>0");
        system("cls");
        return;
    }
    else
    {
        int choise;
        do
        {
            printf("Enter what to show:\n");
            printf("1 - show tour's by date\n");
            printf("2 - show tour's by duration\n");
            printf("0 - to leave\n");
            printf(">>> ");
            choise = check();
        }while(choise < 0 || choise > 2);
        system("cls");
        outputAll(toursList, choise);
    }
    system("pause>0");
    system("cls");
}

void outputAll(struct base toursList, int choise)
{
    if(choise == 1)
    {
        outputHead(toursList, 1);
        for(int i = 0; i < toursList.amount; i++)
        {
            outputOne(i, toursList, 1);
        }
    }

    if(choise == 2)
    {
        outputHead(toursList, 2);

        for(int i = 0; i < toursList.amount; i++)
        {
            outputOne(i, toursList, 2);
        }
    }
}

void outputHead(struct base toursList, int indicator)
{
    int sizeName = findmax(toursList, 1);
    int sizeCost = findmax(toursList, 2);
    int sizeDate = findmax(toursList, 3) + 2;
    int sizeDuration = findmax(toursList, 4);
    if(indicator == 1)
    {
        printf("|Num|");

        printf("Tour name");
        spacePrint(sizeName - strlen("Tour name"));
        printf("|");

        printf("Tour cost");
        spacePrint(sizeCost - strlen("Tour cost"));
        printf("|");

        printf("Tour date");
        spacePrint(sizeDate - strlen("Tour date"));
        printf("|\n");
    }

    if(indicator == 2)
    {
        printf("|Num|");

        printf("Tour name");
        spacePrint(sizeName - strlen("Tour name"));
        printf("|");

        printf("Tour cost");
        spacePrint(sizeCost - strlen("Tour cost"));
        printf("|");

        printf("Tour duration");
        spacePrint(sizeDuration - strlen("Tour duration"));
        printf("|\n");
    }

}

void outputOne(int i, struct base toursList, int choise)
{
    int sizeName = findmax(toursList, 1);
    int sizeCost = findmax(toursList, 2);
    int sizeDate = findmax(toursList, 3);
    int sizeDuration = findmax(toursList, 4);
    int allSizeDate = sizeName + sizeCost + sizeDate;
    int allSizeDuration = sizeName + sizeCost + sizeDuration;

    if(choise == 1)
    {
        if(toursList.tours[i].indicator == 1)
        {
            for(int i = 0; i < allSizeDate + 10; i++)
                printf("-");
            printf("\n");
            printf("| %d |", i+1);
            printf("%s", toursList.tours[i].name);
            spacePrint(sizeName - strlen(toursList.tours[i].name));
            printf("|");

            char *strSpaces = MyItoA(toursList.tours[i].cost);
            printf("%d", toursList.tours[i].cost);
            spacePrint(sizeCost - strlen(strSpaces));
            printf("|");

            for(int k = 0; k < 2; k++)
                printf("%c", toursList.tours[i].info.date[k]);
            printf(".");
            for(int k = 2; k < 4; k++)
                printf("%c", toursList.tours[i].info.date[k]);
            printf(".");
            for(int k = 4; k < 8; k++)
                printf("%c", toursList.tours[i].info.date[k]);
            spacePrint(sizeDate - strlen(toursList.tours[i].info.date));
            printf("|");
            printf("\n");
        }
    }

    if(choise == 2)
    {
        if(toursList.tours[i].indicator == 2)
        {
            for(int i = 0; i < allSizeDuration + 8; i++)
            printf("-");
            printf("\n");

            printf("| %d |", i+1);

            printf("%s", toursList.tours[i].name);
            spacePrint(sizeName - strlen(toursList.tours[i].name));
            printf("|");

            char *strSpaces = MyItoA(toursList.tours[i].cost);
            printf("%d", toursList.tours[i].cost);
            spacePrint(sizeCost - strlen(strSpaces));
            printf("|");

            char *strSpaces2 = MyItoA(toursList.tours[i].info.duration);
            printf("%d", toursList.tours[i].info.duration);
            spacePrint(sizeDuration - strlen(strSpaces2));
            printf("|");
            printf("\n");
        }
    }
}

void spacePrint(int i)
{
    for(int j = 0; j < i; j++)
        printf(" ");
}

char *getString(void)
{
    char c;
    char *temp = NULL;
    int k;
    rewind(stdin);

    for(k = 0; (c = (char)getchar()) != '\n'; k++)
    {
        if((c < 'A' || c > 'Z') && (c < 'a' || c > 'z'))
        {
            printf("\nPlease, enter right format \n>>> ");
            rewind(stdin);
            return NULL;
        }

        if (!(temp = (char*)realloc(temp, (k + 2) * sizeof(char))))
        {
            puts("Retry enter\n");
            return NULL;
        }
        temp[k] = c;
    }
    temp[k] = '\0';
    return temp;
}

int getDigits(int i, struct base toursList)
{
    char temp[9];

    temp[0] = getchar();
    if(temp[0] < '0' || temp[0] > '3')
    {
        printf("\nPlease, enter right format \n>>> ");
        rewind(stdin);
        return 0;
    }

    if(temp[0] == '3')
    {
        temp[1] = getchar();
        if(temp[1] < '0' || temp[1] > '1')
        {
            printf("\nPlease, enter right format \n>>> ");
            rewind(stdin);
            return 0;
        }
    }

    if(temp[0] != '3')
    {
        temp[1] = getchar();
        if(temp[1] < '0' || temp[1] > '9')
        {
            printf("\nPlease, enter right format \n>>> ");
            rewind(stdin);
            return 0;
        }
    }


    temp[2] = getchar();
    if(temp[2] < '0' || temp[2] > '1')
    {
        printf("\nPlease, enter right format \n>>> ");
        rewind(stdin);
        return 0;
    }

    temp[3] = getchar();
    if(temp[3] < '0' || temp[3] > '9')
    {
        printf("\nPlease, enter right format \n>>> ");
        rewind(stdin);
        return 0;
    }


    for(int c = 4; c < 8; c++)
    {
        temp[c] = getchar();
        if(temp[c] < '0' || temp[c] > '9')
        {
            printf("\nPlease, enter right format \n>>> ");
            rewind(stdin);
            return 0;
        }
    }

    if(getchar() != '\n')
    {
        printf("Too many digits!\n ");
        rewind(stdin);
        return 0;
    }

    temp[9] = '\0';

    for(int c = 0; c < 9; c++)
        toursList.tours[i].info.date[c] = temp[c];

    return 1;
}

int check()
{
    char y;
    int x;
    while ( !(scanf("%d%c", &x, &y)) || y != '\n' || x < 0 || x > 214748364)
    {
        rewind(stdin);
        system("cls");
        puts("Please, enter correct format: ");
    }
    return x;
}

void find(struct base toursList)
{
    system("cls");
    if(toursList.tours == NULL)
    {
        system("cls");
        printf("\nTour's not enrolled\n");
        system("pause>0");
        system("cls");
        return;
    }

    else
    {
        int choise;
        do
        {
            do
            {
                puts("\nEnter:");
                puts("1 - to search by tour name");
                puts("2 - to search by tour cost");
                puts("3 - to search by tour date");
                puts("4 - to search by tour duration");
                printf("\n0 - to end search process\n>>> ");
                choise = check();
                system("cls");
            }while(choise < 0 || choise > 4);

            char *temp;
            char *find;

            int iFind = 0, i = 0;
            switch(choise)
            {
                case 1:
                {
                    system("cls");
                    printf("\nEnter name to find\n>>> ");
                    find = getString();
                    uppercase(find);
                    int length = findmax(toursList, 1);
                    temp = (char*)malloc(length * sizeof(char));
                    system("cls");
                    for(i = 0; i < toursList.amount; i++)
                    {
                        strcpy(temp, toursList.tours[i].name);
                        uppercase(temp);
                        if(!strcmp(find, temp))
                        {
                            printf("\n\n");
                            if(toursList.tours[i].indicator == 1)
                            {
                                outputHead(toursList, toursList.tours[i].indicator);
                                outputOne(i, toursList, 1);
                            }
                            if(toursList.tours[i].indicator == 2)
                            {
                                outputHead(toursList, toursList.tours[i].indicator);
                                outputOne(i, toursList, 2);
                            }
                        }
                    }
                    system("pause>0");
                    system("cls");
                    break;
                }

                case 2:
                {
                    system("cls");
                    printf("\nEnter cost to find\n>>> ");
                    iFind = check();
                    system("cls");
                    for(i = 0; i < toursList.amount; i++)
                    {
                        if(iFind == toursList.tours[i].cost)
                        {
                            printf("\n\n");
                            if(toursList.tours[i].indicator == 1)
                            {
                                outputHead(toursList, toursList.tours[i].indicator);
                                outputOne(i, toursList, 1);
                            }
                            if(toursList.tours[i].indicator == 2)
                            {
                                outputHead(toursList, toursList.tours[i].indicator);
                                outputOne(i, toursList, 2);
                            }
                        }
                    }
                    system("pause>0");
                    system("cls");
                    break;
                }

                case 3:
                {
                    system("cls");
                    printf("Enter date to find in format ddmmyyyy\n>>> ");
                    find = (char*)malloc(9 * sizeof(char));
                    gets(find);
                    system("cls");
                    outputHead(toursList, 1);
                    for(i = 0; i < toursList.amount; i++)
                    {
                        if(toursList.tours[i].indicator == 1)
                        {
                            if(!strcmp(find, toursList.tours[i].info.date))
                            {
                                outputOne(i, toursList, 1);
                            }
                        }
                    }
                    system("pause>0");
                    system("cls");
                    break;
                }

                case 4:
                {
                    system("cls");
                    printf("\nEnter duration to find\n>>> ");
                    iFind = check();
                    system("cls");
                    outputHead(toursList, 2);
                    for(i = 0; i < toursList.amount; i++)
                    {
                        if(toursList.tours[i].indicator == 2)
                        {
                            if(iFind == toursList.tours[i].info.duration)
                            {
                                    outputOne(i, toursList, 2);
                            }
                        }
                    }
                    system("pause>0");
                    system("cls");
                    break;
                }
                case 0: return;
            }
        }while(1);
    }
}

int findmax (struct base toursList, int code)
{
    int nameLen = strlen("Tour name");
    int costLen = strlen("Tour cost");
    int dateLen = 8;
    int durationLen = strlen("Tour duration");

    for(int i = 0; i < toursList.amount; i++)
    {
        if(strlen(toursList.tours[i].name) > nameLen)
            nameLen = strlen(toursList.tours[i].name);

        char *CharCost = MyItoA(toursList.tours[i].cost);
        if(strlen(CharCost) > costLen)
            costLen = strlen(CharCost);

        char *CharDuration = MyItoA(toursList.tours[i].info.duration);
        if(strlen(CharDuration) > durationLen)
            durationLen = strlen(CharDuration);
    }

    if(code == 1)
        return nameLen;
    if(code == 2)
        return costLen;
    if(code == 3)
        return dateLen;
    if(code == 4)
        return durationLen;
    return 0;
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

void uppercase(char *find)
{
    int i = 0;
    while (find[i])
    {
        if (find[i] >= 'a' && find[i] <= 'z')
            find[i] -= 32;
        i++;
    }
}

struct base deletion(struct base *toursList)
{
    system("cls");
    if ((*toursList).tours == NULL)
    {
        printf("\nTour's not enrolled\n");
        system("pause>0");
        system("cls");
        return *toursList;
    }

    int choise;



    do
    {
        outputAll(*toursList, 1);
        printf("\n\n");
        outputAll(*toursList, 2);
        do
        {
            printf("\n\nEnter:\n");
            printf("1 - to delete tour by name\n");
            printf("2 - to delete tour by cost\n");
            printf("3 - to delete tour by date\n");
            printf("4 - to delete tour by duration\n");
            printf("5 - to delete tour by number\n");
            printf("0 - to complete the deletion process\n>>> ");
            choise = check();
        }while(choise < 0 || choise > 5);

        char *find;
        char *temp;
        int i, iFind;

        switch(choise)
        {
            case 1:
                {
                    printf("Enter name to delete\n>>> ");
                    find = getString();
                    uppercase(find);
                    int length = findmax(*toursList, 1);
                    temp = (char*)malloc(length * sizeof(char));
                    system("cls");
                    for(i = 0; i < (*toursList).amount; i++)
                    {
                        strcpy(temp, (*toursList).tours[i].name);
                        uppercase(temp);
                        if(strstr(temp,find))
                        {
                            for(int j = i; j < ((*toursList).amount - 1); j++)
                                (*toursList).tours[j] = (*toursList).tours[j+1];
                            (*toursList).amount--;
                            (*toursList).tours = (struct tour*)realloc((*toursList).tours, (*toursList).amount * sizeof(struct tour));
                            i-=1;
                        }
                    }
                    break;
                }

            case 2:
                {
                    printf("\nEnter cost to delete\n>>> ");
                        iFind = check();
                        system("cls");
                        for(i = 0; i < (*toursList).amount; i++)
                        {
                            if(iFind == (*toursList).tours[i].cost)
                            {
                                for(int j = i; j < ((*toursList).amount - 1); j++)
                                    (*toursList).tours[j] = (*toursList).tours[j+1];
                                (*toursList).amount--;
                                (*toursList).tours = (struct tour*)realloc((*toursList).tours, (*toursList).amount * sizeof(struct tour));
                                i-=1;
                            }
                        }
                        break;
                }

            case 3:
                {
                    printf("Enter date to delete in format ddmmyyyy\n>>> ");
                    find = (char*)malloc(9 * sizeof(char));
                    gets(find);
                    temp = (char*)malloc(9 * sizeof(char));
                    system("cls");
                    for(i = 0; i < (*toursList).amount; i++)
                    {
                        strcpy(temp, (*toursList).tours[i].info.date);
                        uppercase(temp);
                        if(strstr(temp,find))
                        {
                            for(int j = i; j < ((*toursList).amount - 1); j++)
                                (*toursList).tours[j] = (*toursList).tours[j+1];
                            (*toursList).amount--;
                            (*toursList).tours = (struct tour*)realloc((*toursList).tours, (*toursList).amount * sizeof(struct tour));
                            i-=1;
                        }
                    }
                    break;
                }

            case 4:
                {
                    printf("\nEnter duration to delete\n>>> ");
                    iFind = check();
                    system("cls");
                    for(i = 0; i < (*toursList).amount; i++)
                    {
                        if(iFind == (*toursList).tours[i].info.duration)
                            {
                                for(int j = i; j < ((*toursList).amount - 1); j++)
                                    (*toursList).tours[j] = (*toursList).tours[j+1];
                                (*toursList).amount--;
                                (*toursList).tours = (struct tour*)realloc((*toursList).tours, (*toursList).amount * sizeof(struct tour));
                                i-=1;
                            }
                    }
                    break;
                }

            case 5:
                {
                    printf("\nEnter the number of the tour you want to remove\n>>> ");
                    int choiseTour = check();
                    system("cls");
                    if (choiseTour == 0)
                        break;

                    for(int j = choiseTour - 1; j < ((*toursList).amount - 1); j++)
                        (*toursList).tours[j] = (*toursList).tours[j+1];

                    (*toursList).amount--;
                    (*toursList).tours = (struct tour*)realloc((*toursList).tours, (*toursList).amount * sizeof(struct tour));
                    break;
                }

            case 0: return *toursList;
        }
       printf("\nRemoval completed\n\n");
    }while(1);

    return *toursList;
}

void printfLongest(struct base toursList)
{
    system("cls");
    outputHead(toursList, 2);
    int temp = 0;
    int numberLongest = 0;
    for(int i = 0; i < toursList.amount; i++)
    {
        if(toursList.tours[i].indicator == 2)
        {
            if(toursList.tours[i].info.duration > temp)
            {
                temp = toursList.tours[i].info.duration;
                numberLongest = i;
            }
        }
    }
    outputOne(numberLongest, toursList, 2);
    system("pause>0");
}
