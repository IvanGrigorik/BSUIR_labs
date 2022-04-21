//
// Created by Ivan on 23.04.2021.
//

#include "fun.h"

void savingFile(struct queue *head)
{
    (void)system("cls");
    if(!emptyCheck(head))
        return;

    int choice;
    do
    {
        puts("Enter format to save");
        puts("Enter 1 to save to .txt file");
        puts("Enter 2 to save to .bin file");
        printf("Enter 0 to exit from saving\n>>> ");
        choice = check();
    }while(choice < 0 || choice > 2);
    system("cls");

    if(choice == 0)
        return;

    printf("Enter file name\n>>> ");
    struct queue *tour = head;
    char carryover = '\n';

    if(choice == 1)
    {
        char *textFileName;
        textFileName = getFileName(1);

        FILE *textFile;
        if(!(textFile = fopen(textFileName, "w+")))
        {
            printf("Can't open file");
            system("pause>0");
            return;
        }

        while(tour)
        {
            fprintf(textFile, "%s ", tour->data.name);
            fprintf(textFile, "%d ", tour->data.cost);
            fprintf(textFile, "%d ", tour->data.indicator);
            if(tour->data.indicator == 1) {
                for(int j = 0; j < 8; j++)
                    fprintf(textFile, "%c", tour->data.info.date[j]);
                fprintf(textFile, "%c", carryover);
            }
            if(tour->data.indicator == 2) {
                fprintf(textFile, "%d\n", tour->data.info.duration);
            }
                tour = tour->next;
        }
        fclose(textFile);
    }

    if(choice == 2)
    {
        char *binFileName;
        binFileName = getFileName(2);

        FILE *binFile;
        if(!(binFile = fopen(binFileName, "wb+")))
        {
            printf("Can't open file");
            system("pause>0");
            return;
        }

        while(tour)
        {
            int tempSize = strlen(tour->data.name);
            fwrite(tour->data.name, sizeof(char), tempSize, binFile);
            fwrite(&tour->data.cost, sizeof(int), 1, binFile);
            fwrite(&tour->data.indicator, sizeof(int), 1, binFile);
            if (tour->data.indicator == 1) {
                fwrite(tour->data.info.date, sizeof(char), 8, binFile);
                fwrite(&carryover, 1, 1, binFile);
            }
            if (tour->data.indicator == 2) {
                    fwrite(&tour->data.info.duration, sizeof(int), 1, binFile);
                    fwrite(&carryover, 1, 1, binFile);
            }
            tour = tour->next;
        }
        fclose (binFile);
    }
}
void inputFromFile(struct queue **head, struct queue **tail)
{
    system("cls");

    int choice;

    do
    {
        puts("Enter format to enter");
        puts("Enter 1 to input from .txt file");
        puts("Enter 2 to input from .bin file");
        printf("Enter 0 to exit from input\n>>> ");
        choice = check();
    }while(choice < 0 || choice > 2);

    system("cls");
    if(choice == 0)
        return;

    *head = NULL;
    *tail = NULL;

    if(choice == 1)
    {
        printf("Enter file name\n>>> ");
        char *textFileName;
        textFileName = getFileName(1);

        FILE *textFile;

        if(!(textFile = fopen(textFileName, "r+")))
        {
            printf("Can't open file");
            system("pause>0");
            return;
        }

        struct queue *tour = NULL;

        while(1)
        {
            if(!(tour = (struct queue *)calloc(1, sizeof(struct queue))))
            {
                puts("Not enough memory");
                system("pause>0");
                system("cls");
                return;
            }

            char *temp = NULL;
            char c;
            int k = 0;

            while(1)
            {
                fscanf(textFile, "%c", &c);
                if(feof(textFile))
                    break;
                if(c == ' ')
                    break;
                if (!(temp = (char*)realloc(temp, (k + 2) * sizeof(char))))
                {
                    clear(head, tail);
                    return;
                }
                temp[k] = c;
                k++;
            }
            if(feof(textFile))
                break;
            temp[k] = '\0';

            tour->data.name = temp;

            if(!(fscanf(textFile, "%d", &k)))
            {
                clear(head, tail);
                return;
            }
            tour->data.cost = k;

            if(!(fscanf(textFile, "%d", &k)))
            {
                clear(head, tail);
                return;
            }
            tour->data.indicator = k;

            if(tour->data.indicator == 1)
            {
                fseek(textFile, 1, SEEK_CUR);
                for(k = 0; k < 8; k++)
                {
                    fscanf(textFile, "%c", &c);
                    if(c < '0' || c > '9')
                    {
                        clear(head, tail);
                        return;
                    }
                    tour->data.info.date[k] = c;
                }
            }
            if(tour->data.indicator == 2)
            {
                fscanf(textFile, "%d", &k);
                tour->data.info.duration = k;
            }

            if (!*head)
                *tail = *head = tour;
            else
            {
                (*tail)->next = tour;
                *tail = tour;
            }

            while(1)
            {
                fscanf(textFile, "%c", &c);
                if((c < 'A' || c > 'Z') && (c < 'a' || c > 'z'))
                    break;
            }
        }
    }
    if(choice == 2)
    {
        printf("Enter file name\n>>> ");
        char *binFileName;
        binFileName = getFileName(2);

        FILE *binFile;

        if(!(binFile = fopen(binFileName, "rb+")))
        {
            printf("Can't open file");
            system("pause>0");
            return;
        }

        struct queue *tour = NULL;

        while(1)
        {
            if(!(tour = (struct queue *)calloc(1, sizeof(struct queue))))
            {
                puts("Not enough memory");
                system("pause>0");
                system("cls");
                return;
            }

            char *temp = NULL;
            char c;
            int k = 0;

            while(1)
            {
                fread(&c, sizeof(char), 1, binFile);

                if(feof(binFile))
                    break;

                if((c < 'A' || c > 'Z')&&(c < 'a' || c > 'z'))
                    break;

                if (!(temp = (char*)realloc(temp, (k + 2) * sizeof(char))))
                {
                    clear(head, tail);
                    return;
                }
                temp[k] = c;
                k++;
            }
            if(feof(binFile))
                break;

            temp[k] = '\0';
            tour->data.name = temp;

            fseek(binFile, -1, SEEK_CUR);

            if(!(fread(&k, sizeof(int), 1, binFile)))
            {
                clear(head, tail);
                return;
            }
            tour->data.cost = k;

            if((fread(&k, sizeof(int), 1, binFile))!= 1)
            {
                clear(head, tail);
                return;
            }
            tour->data.indicator = k;

            if(tour->data.indicator == 1)
            {
                for(int d = 0; d < 8; d++)
                {
                    fread(&c, sizeof(char), 1, binFile);
                    if(c < '0' || c > '9')
                    {
                        clear(head, tail);
                        return;
                    }
                    tour->data.info.date[d] = c;
                }
            }
            if(tour->data.indicator == 2)
            {
                fread(&k, sizeof(int), 1, binFile);
                tour->data.info.duration = k;
            }

            if(!(feof(binFile)))
                fseek(binFile, 1, SEEK_CUR); ///Пофиксить с бинарным файлом !!!!!!!!!!!!!!!!!!!
            else
                break;

            if (!*head)
                *tail = *head = tour;
            else
            {
                (*tail)->next = tour;
                *tail = tour;
            }
        }
        fclose(binFile);
    }
    puts("Tour's loaded successfully");
    system("pause>0");
}
void addElement(struct queue **head, struct queue **tail)
{
    int choice;
    do
    {
        system("cls");
        puts("What do you want to enter?");
        puts("1 - enter by date's");
        puts("2 - enter by duration's");
        printf("0 - to exit\n>>> ");
        choice = check();
    }while(choice < 0 || choice > 2);
    system("cls");

    if(choice == 0)
    {
        system("cls");
        return;
    }

    int much;
    do
    {
        system("cls");
        printf("How much tour's would you enter?\n>>> ");
        much = check();
    }while(much > 100);
    system("cls");

    struct queue *newTour;

    switch(choice)
    {
        case 1:
        {
            for(int i = 0; i < much; i++)
            {
                if(!(newTour = (struct queue*)calloc(1, sizeof(struct queue))))
                {
                    puts("Not enough memory");
                    system("pause>0");
                    system("cls");
                    return;
                }

                printf("Tour %d:\n", i+1);

                do
                {
                    printf("Enter tour name: ");
                    rewind(stdin);
                }while(!(newTour->data.name = getString()));

                do
                {
                    printf("Enter tour cost: ");
                    rewind(stdin);
                }while(!(newTour->data.cost = check()));

                do
                {
                    printf("Enter tour date in format ddmmyyyy: ");
                    rewind(stdin);
                }while(!getDigits(newTour));

                newTour->data.indicator = 1;

                if (!*head)
                    *tail = *head = newTour;
                else
                {
                    (*tail)->next = newTour;
                    *tail = newTour;
                }
                system("cls");
            }
            break;
        }

        case 2:
        {
            for(int i = 0; i < much; i++)
            {
                if(!(newTour = (struct queue*)calloc(1, sizeof(struct queue))))
                {
                    puts("Not enough memory");
                    system("pause>0");
                    system("cls");
                    return;
                }

                system("cls");
                printf("Tour number %d of %d\n", i+1, much);

                do
                {
                    printf("Enter tour name: ");
                    rewind(stdin);
                }while(!(newTour->data.name = getString()));

                do
                {
                    printf("Enter tour cost: ");
                    rewind(stdin);
                }while(!(newTour->data.cost = check()));

                do
                {
                    printf("Enter tour duration: ");
                    rewind(stdin);
                }while(!(newTour->data.info.duration = check()));

                newTour->data.indicator = 2;

                if (!*head)
                    *tail = *head = newTour;
                else
                {
                    (*tail)->next = newTour;
                    *tail = newTour;
                }
                system("cls");
            }
            break;
        }
    }
    system("cls");
}
void output(struct queue *tourList)
{
    system("cls");

    int sizeName = findMax(tourList, 1);

    if(!emptyCheck(tourList))
        return;

    else
    {
        struct queue *tour = tourList;
        int i = 0;

        outputHead(tour);

        while(tour)
        {
            outputOne(tour, i, sizeName);
            tour = tour->next;
            i++;
        }
    }
}
void search(struct queue *toursList)
{
    system("cls");
    if(!emptyCheck(toursList))
        return;

    else
    {
        int choice;
        do
        {
            struct queue *tour = toursList;
            do
            {
                puts("\nEnter:");
                puts("1 - to search by tour name");
                puts("2 - to search by tour cost");
                puts("3 - to search by tour date");
                puts("4 - to search by tour duration");
                printf("\n0 - to end search process\n>>> ");
                choice = check();
                system("cls");
            }while(choice < 0 || choice > 4);

            char *temp;
            char *find;

            int iFind, i = 0;
            int sizeName = findMax(toursList, 1);
            switch(choice)
            {
                case 1:
                {
                    system("cls");
                    printf("\nEnter name to find\n>>> ");
                    find = getString();
                    uppercase(find);
                    int length = findMax(tour, 1);
                    temp = (char*)malloc(length * sizeof(char));
                    system("cls");
                    outputHead(tour);
                    while(tour)
                    {
                        strcpy(temp, tour->data.name);
                        uppercase(temp);
                        if(!strcmp(find, temp))
                            outputOne(tour, i+1, sizeName);
                        i++;
                        tour = tour->next;
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
                    outputHead(tour);
                    while(tour)
                    {
                        if(tour->data.cost == iFind)
                            outputOne(tour, i+1, sizeName);

                        i++;
                        tour = tour->next;
                    }
                    system("pause>0");
                    system("cls");
                    break;
                }

                case 3:
                {
                    system("cls");
                    printf("Enter date to find in format ddmmyyyy\n>>> ");
                    char dateFind[9];
                    gets(dateFind);
                    temp = (char *)calloc(9,sizeof(char));
                    system("cls");
                    outputHead(tour);
                    while(tour)
                    {
                        if(tour->data.indicator == 1)
                        {
                            strcpy(temp, tour->data.info.date);
                            uppercase(temp);
                            if(!strcmp(dateFind, temp))
                                outputOne(tour, i+1, sizeName);
                        }
                        i++;
                        tour = tour->next;
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
                    outputHead(tour);
                    while(tour)
                    {
                        if(tour->data.indicator == 2)
                            if(iFind == tour->data.info.duration)
                                outputOne(tour, i+1, sizeName);

                        i++;
                        tour = tour->next;
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
void delete(struct queue **head, struct queue **tail)
{
    system("cls");
    if(!emptyCheck(*head))
        return;

    do
    {
        struct queue *tour = *head;
        struct queue *preTour = *head;

        int choice;

        if(!emptyCheck(*head))
            return;

        output(tour);


        do
        {
            puts("\nEnter 0 to end delete process");
            printf("Enter number to delete\n>>> ");
            choice = check();
        }while(choice < 0);

        if(choice == 0)
            return;

        for(int i = 1; i < choice && tour != NULL; i++)
        {
            tour = tour->next;
            if(tour == NULL)
            {
                printf("No such element");
                return;
            }
        }
        if(tour == *head)
        {
            *head = (*head) -> next;
            free(tour);
            system("cls");
            continue;
        }
        if(tour == *tail)
        {
            while(preTour->next != tour)
                preTour = preTour->next;
            *tail = preTour;
            (*tail)->next = tour->next;
            free(tour);
        }
        else
        {
            while(preTour->next != tour)
                preTour = preTour->next;
            preTour->next = tour->next;
            free(tour);
        }
    }while(1);
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
int menu()
{
    puts("\nEnter: ");
    puts("1) Add tour's");
    puts("2) Save tour's in file");
    puts("3) Input tour's from file");
    puts("4) Show tour's");
    puts("5) Search tour's");
    puts("6) Delete tour's");
    puts("0) Close program");
    printf(">>> ");
    int x;
    x = check();
    return x;
}
void outputHead(struct queue *toursList)
{
    int sizeName = findMax(toursList, 1);
    int sizeCost = findMax(toursList, 2);
    int sizeDate = findMax(toursList, 3) + 2;
    int sizeDuration = findMax(toursList, 4);

    printf("|Num|");

    printf("Tour name");
    spacePrint(sizeName - strlen("Tour name"));
    printf("|");

    printf("Tour cost");
    spacePrint(sizeCost - strlen("Tour cost"));
    printf("|");

    printf("Tour date");
    spacePrint(sizeDate - strlen("Tour date"));
    printf("|");

    printf("Tour duration");
    spacePrint(sizeDuration - strlen("Tour duration"));
    printf("|\n");
}
void outputOne(struct queue *tour, int i, int sizeName)
{
    int sizeCost = findMax(tour, 2);
    int sizeDate = findMax(tour, 3);
    int sizeDuration = findMax(tour, 4);
    int allSize = sizeName + sizeCost + sizeDate + sizeDuration;

    for(int j = 0; j < allSize + 11; j++)
        printf("-");
    printf("\n");

    if(i < 9)
        printf("|%d  |", i+1);
    else
        printf("|%d |", i+1);
    printf("%s", tour->data.name);
    spacePrint(sizeName - strlen(tour->data.name));
    printf("|");

    char *strSpaces = MyItoA(tour->data.cost);
    printf("%d", tour->data.cost);
    spacePrint(sizeCost - strlen(strSpaces));
    printf("|");

    if(tour->data.indicator == 1)
    {
        for(int k = 0; k < 2; k++)
            printf("%c", tour->data.info.date[k]);
        printf(".");
        for(int k = 2; k < 4; k++)
            printf("%c", tour->data.info.date[k]);
        printf(".");
        for(int k = 4; k < 8; k++)
            printf("%c", tour->data.info.date[k]);
        spacePrint(sizeDate - strlen(tour->data.info.date));
        printf("|");
    }
    else
        printf("----------|");

    if(tour->data.indicator == 2)
    {
        char *strSpaces2 = MyItoA(tour->data.info.duration);
        printf("%d", tour->data.info.duration);
        spacePrint(sizeDuration - strlen(strSpaces2));
        printf("|");
        printf("\n");
    }
    else
    {
        for(int k = 0; k < sizeDuration; k++)
            printf("-");
        printf("|");
        printf("\n");
    }
}
void spacePrint(int i)
{
    for(int j = 0; j < i; j++)
        printf(" ");
}
int findMax(struct queue *toursList, int code)
{
    int nameLen = strlen("Tour name");
    int costLen = strlen("Tour cost");
    int dateLen = 8;
    int durationLen = strlen("Tour duration");

    while(toursList)
    {
        if(strlen(toursList->data.name) > nameLen)
            nameLen = strlen(toursList->data.name);

        char *CharCost = MyItoA(toursList->data.cost);
        if(strlen(CharCost) > costLen)
            costLen = strlen(CharCost);

        char *CharDuration = MyItoA(toursList->data.info.duration);
        if(strlen(CharDuration) > durationLen)
            durationLen = strlen(CharDuration);

        toursList = toursList->next;
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
int check()
{
    char y;
    int x;
    while (scanf("%d%c", &x, &y) != 2 || y != '\n' || x < 0/* || !x*/)
    {
        rewind(stdin);
        puts("\nPlease, enter correct format: ");
    }
    return x;
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
int getDigits(struct queue *tourList)
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

    for(int i = 0; i < 9; i++)
        tourList->data.info.date[i] = temp[i];
    return 1;
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
int emptyCheck(struct queue *head)
{
    if(head == NULL)
    {
        printf("Tour's not enrolled\n");
        system("pause>0");
        return 0;
    }
    return 1;
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
            system("pause>0");
            rewind(stdin);
            return NULL;
        }

        if (!(temp = (char*)realloc(temp, (k + 6) * sizeof(char))))
        {
            rewind(stdin);
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
void clear(struct queue **head, struct queue **tail)
{
    printf("Retry input please");
    system("pause>0");
    *head = NULL;
    *tail = NULL;
    return;
}