#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functionshead.h"

int menu()
{
    puts("\nEnter: ");
	puts("1) Add pupil");
	puts("2) Show pupil's");
	puts("3) Change pupil");
	puts("4) Search pupil's");
	puts("5) Sort pupil's");
	puts("6) Delete pupil");
	puts("7) Search by partial match");
    puts("0) Close program");
    printf(">>> ");
	int x;
	x = check(x);
	return x;
}

int check(int x)
{
    char y;
    while ( !(scanf("%d%c", &x, &y)) || y != '\n' || x < 0)
    {
        rewind(stdin);
        puts("Please, enter correct format: ");
    }
    return x;
}

struct base enter(struct base journal)
{
    system("cls");
    printf("\nHow much pupils you would enter?\n>>> ");
    int num;
    num = check(num);
    struct base *temp;
    journal.amount += num;
    if (!(temp = (struct pupil*)realloc(journal.pupils, journal.amount * sizeof(struct pupil))))
    {
        journal.amount -= num;
        puts("Not enough memory to add new pupil!");
        return journal;
    }
    journal.pupils = temp;

    static int k = 0;
    for(int i = journal.amount - num; i < journal.amount; i++)
    {
        printf("\nPupil %d\n", ++k);

        do
        {
            printf("Enter name: ");
            fflush(stdin);
        }while(!strGet(i, journal, "name"));

        do
        {
            printf("Enter last name: ");
            fflush(stdin);
        }while(!strGet(i, journal, "lastName"));

        do
        {
            printf("Enter middle name: ");
            fflush(stdin);
        }while(!strGet(i, journal, "patronymic"));

        printf("Enter class: ");
        fflush(stdin);
        journal.pupils[i].clas = check(journal.pupils[i].clas);

        do
        {
            printf("Enter phone number with 9 digits: ");
            fflush(stdin);
        }while(!(getDigits(i, journal)));

        for (int j = 0; j < 4; j++)
        {
            printf("Enter the grade for exam #%d ", j + 1);
            journal.pupils[i].marks[j] = check(journal.pupils[i].marks[j]);
        }
    }
    system("cls");
    return journal;
}

int strGet(int i, struct base journal, char *code)
{
    char c;
    int k;

    for(k = 0; (c = getchar()) != '\n'; k++)
    {
        if((c < 'A' || c > 'Z') && (c < 'a' || c > 'z'))
        {
            printf("\nPlease, enter right format \n>>> ");
            rewind(stdin);
            return 0;
        }

            if(code == "name")
                journal.pupils[i].name[k] = c;
            if(code == "lastName")
                journal.pupils[i].lastName[k] = c;
            if(code == "patronymic")
                journal.pupils[i].patronymic[k] = c;

    }
    if(code == "name")
        journal.pupils[i].name[k] = '\0';
    if(code == "lastName")
        journal.pupils[i].lastName[k] = '\0';
    if(code == "patronymic")
        journal.pupils[i].patronymic[k] = '\0';
    return 1;
}

int getDigits(int i, struct base journal)
{
    char temp[10];
    for(int c = 0; c < 9; c++)
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

    temp[10] = '\0';

    for(int c = 0; c < 10; c++)
    {
        journal.pupils[i].number[c] = temp[c];
    }
    return 1;
}

void output(struct base journal)
{
    system("cls");
    int choise, k = 0;

    if (journal.pupils == NULL)
    {
        printf("\nPupil's not enrolled\n");
        system("pause>0");
        system("cls");
        return;
    }
    else
    {
        puts("\nWhat would you like to do?");
        puts("1 - display any pupil");
        puts("2 - show all pupil's");
        printf(">>> ");
        choise = check(choise);

        int i = 0;
        if(choise == 1)
        {
            system("cls");
            puts("\nEnter pupil number, what you want to output");
            printf("\n>>> ");
            k = check(k);
            outputOne(k-1, journal);
        }
        if(choise == 2)
        {
            system("cls");
            for(i = 0; i < journal.amount; i++)
            {
                outputOne(i, journal);
            }
        }
    }
    system("pause>0");
    system("cls");
}

void outputOne(int i, struct base journal)
{
    printf("\nName: %s\n", journal.pupils[i].name);
    printf("Last name: %s\n", journal.pupils[i].lastName);
    printf("Middle name: %s\n", journal.pupils[i].patronymic);
    printf("Phone number: %s\n", journal.pupils[i].number);
    printf("Class: %d\n", journal.pupils[i].clas);
    for(int j = 0; j < 4; j++)
        printf("Mark for %d exam: %d\n", j+1, journal.pupils[i].marks[j]);
    printf("\n");
}

void change(struct base journal)
{
    system("cls");
    if (journal.pupils == NULL)
    {
        printf("\nPupil's not enrolled\n");
        system("pause>0");
        system("cls");
        return;
    }

    else
    {
        int changeNum, choise;
        printf("\nEnter number, what you want to change\n>>> ");
        changeNum = check(changeNum);
        do
        {
            do
            {
                showMenu("change");
                choise = check(choise);
                printf("\nPlease, enter right number!\n");

            }while(choise < 0 || choise > 7);

            switch(choise)
            {
                case 1:
                printf("Enter new name\n>>> ");
                gets(journal.pupils[changeNum-1].name);
                break;

                case 2:
                printf("Enter new last name\n>>> ");
                gets(journal.pupils[changeNum-1].lastName);
                break;

                case 3:
                printf("Enter new middle name\n>>> ");
                gets(journal.pupils[changeNum-1].patronymic);
                break;

                case 4:
                printf("Enter new class\n>>> ");
                journal.pupils[changeNum-1].clas = check(journal.pupils[changeNum-1].clas);
                break;

                case 5:
                do
                {
                    printf("Enter new phone number\n");
                    printf("No more than 9 digits\n>>> ");
                    fflush(stdin);
                }while(!(getDigits(changeNum - 1, journal)));
                break;

                case 6:
                printf("Enter new grade for exam's: \n");
                for (int j = 0; j < 4; j++)
                {
                    printf("Enter the grade for exam #%d ", j + 1);
                    journal.pupils[changeNum - 1].marks[j] = check(journal.pupils[changeNum - 1].marks[j]);
                }
                break;

                case 7:
                    system("cls");

                case 0:
                    return;
            }
        }while(1);
    }
    system("cls");
}

void find(struct base journal)
{
    system("cls");
    if (journal.pupils == NULL)
    {
        printf("\nPupil's not enrolled\n");
        system("pause>0");
        system("cls");
        return;
    }

    else
    {
        int choise;
        do{
            do{
                showMenu("search");
                choise = check(choise);
            }while(choise < 0 || choise > 7);

            char find[20], temp[20];
            int iFind = 0, examChoise = 0, i = 0;

            switch(choise)
            {
                case 1:
                {
                    printf("Enter name to find\n>>> ");
                    gets(find);
                    uppercase(find);
                    for(i = 0; i < journal.amount; i++)
                    {
                        strcpy(temp, journal.pupils[i].name);
                        uppercase(temp);
                        if(!strcmp(find, temp))
                        {
                            outputOne(i, journal);
                        }
                    }
                    break;
                }

                case 2:
                {
                    printf("Enter last name to find\n>>> ");
                    gets(find);
                    uppercase(find);
                    for(i = 0; i < journal.amount; i++)
                    {
                        strcpy(temp, journal.pupils[i].lastName);
                        uppercase(temp);
                        if(!strcmp(find, temp))
                        {
                            outputOne(i, journal);
                        }
                    }
                    break;
                }

                case 3:
                {
                    printf("Enter middle name to find\n>>> ");
                    gets(find);
                    uppercase(find);
                    for(i = 0; i < journal.amount; i++)
                    {
                        strcpy(temp, journal.pupils[i].patronymic);
                        uppercase(temp);
                        if(!strcmp(find, temp))
                        {
                            outputOne(i, journal);
                        }
                    }
                    break;
                }

                case 4:
                {
                    printf("Enter class to find\n>>> ");
                    iFind = check(iFind);
                    for(i = 0; i < journal.amount; i++)
                    {
                        if(journal.pupils[i].clas == iFind)
                        {
                            outputOne(i, journal);
                        }
                    }
                    break;
                }

                case 5:
                {
                    printf("Enter phone number to find\n>>> ");
                    gets(find);
                    for(i = 0; i < journal.amount; i++)
                    {
                        if(!strcmp(find, journal.pupils[i].number))
                        {
                            outputOne(i, journal);
                        }
                    }
                    break;
                }

                case 6:
                {
                    do
                    {
                        showExam();
                        examChoise = check(examChoise);
                    }while(examChoise < 0 || examChoise > 4);
                    printf("Enter mark\n>>> ");
                    iFind = check(iFind);

                    for(i = 0; i < journal.amount; i++)
                    {
                        if(journal.pupils[i].marks[examChoise] == iFind)
                        {
                            outputOne(i, journal);
                        }
                    }
                    break;
                }
                case 0: return;

                case 7:
                    system("cls");
            }
        }while(1);
    }
    system("cls");
}

void uppercase(char find[20])
{
    int i = 0;
    while (find[i])
    {
        if (find[i] >= 'a' && find[i] <= 'z')
            find[i] -= 32;
        i++;
    }
}

void sort(struct base journal)
{
    system("cls");
    if (journal.pupils == NULL)
    {
        printf("\nPupil's not enrolled\n");
        system("pause>0");
        system("cls");
        return;
    }

    else
    {
        struct pupil tmp;
        int i = 0, j = 0;

        int choiseSort;
        int choise;
        do
        {
            do
            {
                puts("Enter 1 to sort from smallest to largest ");
                puts("Enter 2 to sort from largest to smaller");
                puts("Enter 0 to end sort process");
                puts("Enter 3 to clean last operation");
                printf(">>> ");
                choiseSort = check(choiseSort);
            }while(choiseSort < 0 || choiseSort > 3);

            switch(choiseSort)
            {
                case 1:
                {
                    do
                    {
                        showMenu("sort");
                        choise = check(choise);
                    }while(choise < 0 || choise > 6);

                    char temp[20], temp2[20];

                    switch(choise)
                    {
                        case 1:
                        {
                            for(i = 0; i < journal.amount-1; i++)
                                for(j = i + 1; j < journal.amount; j++)
                                {
                                    strcpy(temp, journal.pupils[i].name);
                                    uppercase(temp);
                                    strcpy(temp2, journal.pupils[j].name);
                                    uppercase(temp2);
                                    if(strcmp(temp, temp2) > 0)
                                    {
                                        tmp = journal.pupils[i];
                                        journal.pupils[i] = journal.pupils[j];
                                        journal.pupils[j] = tmp;
                                    }
                                }
                            puts("\nSorting is over");
                            break;
                        }

                        case 2:
                        {
                            for(i = 0; i < journal.amount-1; i++)
                                for(j = i + 1; j < journal.amount; j++)
                                {
                                    strcpy(temp, journal.pupils[i].lastName);
                                    uppercase(temp);
                                    strcpy(temp2, journal.pupils[j].lastName);
                                    uppercase(temp2);
                                    if(strcmp(temp, temp2) > 0)
                                    {
                                        tmp = journal.pupils[i];
                                        journal.pupils[i] = journal.pupils[j];
                                        journal.pupils[j] = tmp;
                                    }
                                }
                            puts("\nSorting is over");
                            break;
                        }

                        case 3:
                        {
                            for(i = 0; i < journal.amount-1; i++)
                                for(j = i + 1; j < journal.amount; j++)
                                {
                                    strcpy(temp, journal.pupils[i].patronymic);
                                    uppercase(temp);
                                    strcpy(temp2, journal.pupils[j].patronymic);
                                    uppercase(temp2);

                                    if(strcmp(temp, temp2) > 0)
                                    {
                                        tmp = journal.pupils[i];
                                        journal.pupils[i] = journal.pupils[j];
                                        journal.pupils[j] = tmp;
                                    }
                                }
                            puts("\nSorting is over");
                            break;
                        }


                      // Class sort
                      case 4:
                      {
                            for (int i = 0; i < journal.amount - 1; i++)
                            {
                                for (int j = (journal.amount - 1); j > i; j--)
                                {
                                    if (journal.pupils[j - 1].clas > journal.pupils[j].clas)
                                    {
                                        int temp = journal.pupils[j - 1].clas;
                                        journal.pupils[j - 1].clas = journal.pupils[j].clas;
                                        journal.pupils[j].clas = temp;
                                    }
                                }
                            }
                      }

                      // Phone number sort
                        case 5:
                        {
                            for(i = 0; i < journal.amount-1; i++)
                                for(j = i + 1; j < journal.amount; j++)
                                {
                                    strcpy(temp, journal.pupils[i].number);

                                    if(strcmp(temp, journal.pupils[j].number) > 0)
                                    {
                                        tmp = journal.pupils[i];
                                        journal.pupils[i] = journal.pupils[j];
                                        journal.pupils[j] = tmp;
                                    }
                                }
                            puts("\nSorting is over");
                            break;
                        }

                        case 6:
                        {
                            puts("Enter for which exam you want to search\n");
                            puts("1 - Maths");
                            puts("2 - Physics");
                            puts("3 - Russian language");
                            puts("4 - Literature");
                            printf(">>> ");
                            int examChoise = check(examChoise);

                            for (int i = 0; i < journal.amount - 1; i++)
                            {
                                for (int j = (journal.amount - 1); j > i; j--)
                                {
                                    if (journal.pupils[j - 1].marks[examChoise] > journal.pupils[j].marks[examChoise])
                                    {
                                        tmp = journal.pupils[j - 1];
                                        journal.pupils[j - 1] = journal.pupils[j];
                                        journal.pupils[j] = tmp;
                                    }
                                }
                            }
                            puts("\nSorting is over");
                            break;
                        }
                      case 0: return;
                    }
                }
                case 2:
                {
                     do
                    {
                        showMenu("sort");
                        choise = check(choise);
                    }while(choise < 0 || choise > 6);

                    char temp[20], temp2[20];

                    switch(choise)
                    {
                        case 1:
                        {
                            for(i = 0; i < journal.amount-1; i++)
                                for(j = i + 1; j < journal.amount; j++)
                                {
                                    strcpy(temp, journal.pupils[i].name);
                                    uppercase(temp);
                                    strcpy(temp2, journal.pupils[j].name);
                                    uppercase(temp2);
                                    if(strcmp(temp, temp2) < 0)
                                    {
                                        tmp = journal.pupils[i];
                                        journal.pupils[i] = journal.pupils[j];
                                        journal.pupils[j] = tmp;
                                    }
                                }
                            puts("\nSorting is over");
                            break;
                        }

                        case 2:
                        {
                            for(i = 0; i < journal.amount-1; i++)
                                for(j = i + 1; j < journal.amount; j++)
                                {
                                    strcpy(temp, journal.pupils[i].lastName);
                                    uppercase(temp);
                                    strcpy(temp2, journal.pupils[j].lastName);
                                    uppercase(temp2);
                                    if(strcmp(temp, temp2) < 0)
                                    {
                                        tmp = journal.pupils[i];
                                        journal.pupils[i] = journal.pupils[j];
                                        journal.pupils[j] = tmp;
                                    }
                                }
                            puts("\nSorting is over");
                            break;
                        }

                        case 3:
                        {
                            for(i = 0; i < journal.amount-1; i++)
                                for(j = i + 1; j < journal.amount; j++)
                                {
                                    strcpy(temp, journal.pupils[i].patronymic);
                                    uppercase(temp);
                                    strcpy(temp2, journal.pupils[j].patronymic);
                                    uppercase(temp2);

                                    if(strcmp(temp, temp2) < 0)
                                    {
                                        tmp = journal.pupils[i];
                                        journal.pupils[i] = journal.pupils[j];
                                        journal.pupils[j] = tmp;
                                    }
                                }
                            puts("\nSorting is over");
                            break;
                        }


                      // Class sort
                      case 4:
                      {
                            for (int i = 0; i < journal.amount - 1; i++)
                            {
                                for (int j = (journal.amount - 1); j > i; j--)
                                {
                                    if (journal.pupils[j - 1].clas < journal.pupils[j].clas)
                                    {
                                        int temp = journal.pupils[j - 1].clas;
                                        journal.pupils[j - 1].clas = journal.pupils[j].clas;
                                        journal.pupils[j].clas = temp;
                                    }
                                }
                            }
                      }

                      // Phone number sort
                        case 5:
                        {
                            for(i = 0; i < journal.amount-1; i++)
                                for(j = i + 1; j < journal.amount; j++)
                                {
                                    strcpy(temp, journal.pupils[i].number);

                                    if(strcmp(temp, journal.pupils[j].number) < 0)
                                    {
                                        tmp = journal.pupils[i];
                                        journal.pupils[i] = journal.pupils[j];
                                        journal.pupils[j] = tmp;
                                    }
                                }
                            puts("\nSorting is over");
                            break;
                        }

                        case 6:
                        {
                            puts("Enter for which exam you want to search\n");
                            puts("1 - Maths");
                            puts("2 - Physics");
                            puts("3 - Russian language");
                            puts("4 - Literature");
                            printf(">>> ");
                            int examChoise = check(examChoise);

                            for (int i = 0; i < journal.amount - 1; i++)
                            {
                                for (int j = (journal.amount - 1); j > i; j--)
                                {
                                    if (journal.pupils[j - 1].marks[examChoise] < journal.pupils[j].marks[examChoise])
                                    {
                                        tmp = journal.pupils[j - 1];
                                        journal.pupils[j - 1] = journal.pupils[j];
                                        journal.pupils[j] = tmp;
                                    }
                                }
                            }
                            puts("\nSorting is over");
                            break;
                        }
                      case 0: return;
                    }
                }

                case 0:
                    return;

            }


        }while(1);
    }
    system("cls");
}

struct base deletion(struct base *journal)
{
    system("cls");
    if ((*journal).pupils == NULL)
    {
        printf("\nPupil's not enrolled\n");
        system("pause>0");
        system("cls");
        return *journal;
    }

    int choise;
    do
    {
        do
        {
            printf("\nEnter the number of the pupil you want to remove");
            printf("\nEnter 0 to complete the deletion process\n>>> ");
            choise = check(choise);
        }while(choise < 0 || choise > (*journal).amount);

        if(choise == 0)
            return *journal;

        for(int i = (choise-1); i < ((*journal).amount-1); i++)
            (*journal).pupils[i] = (*journal).pupils[i+1];

        (*journal).amount--;
        (*journal).pupils = (struct pupil*)realloc((*journal).pupils, (*journal).amount * sizeof(struct pupil));
        printf("\nRemoval completed\n\n");

    }while(1);
    system("cls");
    return *journal;
}

void partialSearch(struct base journal)
{
    system("cls");
    if (journal.pupils == NULL)
    {
        printf("\nPupil's not enrolled\n");
        system("pause>0");
        system("cls");
        return;
    }

    else
    {
        int choise = 0, i = 0, j = 0, intTemp;
        char find[20], temp[20];
        do
        {
            do
            {
                showMenu("partial search");
                choise = check(choise);
            }while(choise < 0 || choise > 7);

            switch(choise)
            {
                case 1:
                {
                    printf("Enter name to find\n>>> ");
                    gets(find);
                    uppercase(find);
                    for(i = 0; i < journal.amount; i++)
                    {
                        strcpy(temp, journal.pupils[i].name);
                        uppercase(temp);
                        if(strstr(temp, find))
                        {
                            outputOne(i, journal);
                            j = 1;
                        }
                    }
                    if(j == 0)
                        printf("\n\nPupils not found\n\n");
                    break;
                }

                case 2:
                {
                    printf("Enter last name to find\n>>> ");
                    gets(find);
                    uppercase(find);
                    for(i = 0; i < journal.amount; i++)
                    {
                        strcpy(temp, journal.pupils[i].lastName);
                        uppercase(temp);
                        if(strstr(temp, find))
                        {
                            outputOne(i, journal);
                            j = 1;
                        }
                    }
                    if(j == 0)
                        printf("\n\nPupils not found\n\n");
                    break;
                }

                case 3:
                {
                    printf("Enter middle name to find\n>>> ");
                    gets(find);
                    uppercase(find);
                    for(i = 0; i < journal.amount; i++)
                    {
                        strcpy(temp, journal.pupils[i].patronymic);
                        uppercase(temp);
                        if(strstr(temp, find))
                        {
                            outputOne(i, journal);
                            j = 1;
                        }
                    }
                    if(j == 0)
                        printf("\n\nPupils not found\n\n");
                    break;
                }

                case 4:
                {
                    printf("Enter class number to find\n>>> ");
                    gets(find);
                    uppercase(find);
                    for(i = 0; i < journal.amount; i++)
                    {
                        int intTemp = journal.pupils[i].clas;
                        itoa(intTemp, temp, 10);
                        if(strstr(temp, find))
                            {
                                outputOne(i, journal);
                                j = 1;
                            }
                        if (j == 0)
                            printf("\n\nPupils not found\n\n");
                    }
                    break;
                }

                case 5:
                {
                    printf("Enter phone number to find\n>>> ");
                    gets(find);
                    for(i = 0; i < journal.amount; i++)
                    {
                        if(strstr(journal.pupils[i].number, find))
                        {
                            outputOne(i, journal);
                            j = 1;
                        }
                    }
                    if(j == 0)
                        printf("\n\nPupils not found\n\n");
                    break;
                }

                case 6:
                {

                    int examChoise = 0;
                    do
                    {
                        showExam();
                        examChoise = check(examChoise);
                    }while(examChoise < 0 || examChoise > 4);

                    printf("Enter exam mark to find\n>>> ");
                    gets(find);

                    for(i = 0; i < journal.amount; i++)
                    {
                        int intTemp = journal.pupils[i].marks[examChoise];
                        itoa(intTemp, temp, 10);
                        if(strstr(temp, find))
                            {
                                outputOne(i, journal);
                                j = 1;
                            }
                        if (j == 0)
                            printf("\n\nPupils not found\n\n");
                    }
                    break;
                }

                case 7:
                    system("cls");

                case 0: return;
            }

        }while(1);
    }
    system("cls");
}

void showMenu(char *s)
{
    printf("\nEnter: ");
    printf("\n1 - to %s by name", s);
    printf("\n2 - to %s by last name", s);
    printf("\n3 - to %s by middle name", s);
    printf("\n4 - to %s by class", s);
    printf("\n5 - to %s by phone number", s);
    printf("\n6 - to %s by graduate for exam", s);
    printf("\n0 - to end %s process", s);
    printf("\n7 - to clean last operation");
    printf("\n>>> ");
}

void showExam()
{
    puts("Enter for which exam you want to search\n");
    puts("1 - Maths");
    puts("2 - Physics");
    puts("3 - Russian language");
    puts("4 - Literature");
    printf(">>> ");
}
