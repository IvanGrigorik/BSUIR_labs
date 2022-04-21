#include "head.h"

void saveFileElement(struct stack **toursList, FILE *binaryFile, FILE *textFile)
{
    system("cls");
    if(toursList == NULL)
    {
        printf("Tour's not enrolled\n");
        system("pause>0");
        system("cls");
        return;
    }

    reverseStack(toursList);

    int choise;

    do
    {
        puts("Enter format to save");
        puts("Enter 1 to save to .txt file");
        puts("Enter 2 to save to .bin file");
        printf("Enter 0 to exit from saving\n>>> ");
        choise = check();
    }while(choise < 0 || choise > 2);

    system("cls");
    if(choise == 0)
        return;
    if(choise == 1)
    {
        printf("Enter file name\n>>> ");
        char *txtName;
        txtName = getFileName(1);
        if(!(textFile = fopen(txtName, "w+")))
        {
            printf("Can't open file");
            system("pause>0");
            reverseStack(toursList);
            return;
        }
    }
    else if(choise == 2)
    {
        printf("Enter file name\n>>> ");
        char *binName;
        binName = getFileName(2);
        if(!(binaryFile = fopen(binName, "w+b")))
        {
            printf("Can't open file");
            system("pause>0");
            reverseStack(toursList);
            return;
        }
    }
    struct stack *newTour = *toursList;

    int tempSize;
    char c = '\n';

    while(newTour)
    {
        tempSize = strlen(newTour->data.name);

        if(choise == 1)
        {
            fprintf(textFile, "%s ", newTour->data.name);
            fprintf(textFile, "%d ", newTour->data.cost);
            fprintf(textFile, "%d ", newTour->data.indicator);
            if(newTour->data.indicator == 1)
                    fprintf(textFile, "%s\n", newTour->data.info.date);
            if(newTour->data.indicator == 2)
                    fprintf(textFile, "%d\n", newTour->data.info.duration);
        }
        if(choise == 2)
        {
            fwrite(newTour->data.name, sizeof(char), tempSize, binaryFile);
            fwrite(&newTour->data.cost, sizeof(int), 1, binaryFile);
            fwrite(&newTour->data.indicator, sizeof(int), 1, binaryFile);
            if(newTour->data.indicator == 1)
            {
                fwrite(newTour->data.info.date, sizeof(char), 8, binaryFile);
                fwrite(&c, 1, 1, binaryFile);
            }
            if(newTour->data.indicator == 2)
            {
                if(choise == 2)
                {
                    fwrite(&newTour->data.info.duration, sizeof(int), 1, binaryFile);
                    fwrite(&c, 1, 1, binaryFile);
                }
            }
        }
        newTour = newTour->next;
    }

    system("cls");
    reverseStack(toursList);
    if(choise == 2)
        fclose(binaryFile);
    if(choise == 1)
        fclose(textFile);
    puts("Stack saved successfully");
    system("pause>0");
    return;
}

void inputFromFile(struct stack **toursList, FILE *binaryFile, FILE *textFile)
{
    *toursList = NULL;
    system("cls");

    int choise;

    do
    {
        puts("Enter format to save");
        puts("Enter 1 to input from .txt file");
        puts("Enter 2 to input from .bin file");
        printf("Enter 0 to exit from input\n>>> ");
        choise = check();
    }while(choise < 0 || choise > 2);

    system("cls");
    if(choise == 0)
        return;

    if(choise == 1)
    {
        printf("Enter file name\n>>> ");
        char *txtName;
        txtName = getFileName(1);

        if(!(textFile = fopen(txtName, "r+")))
        {
            printf("Can't open file");
            system("pause>0");
            return;
        }
        struct stack *newTour = NULL;

        while(1)
        {
            if(!(newTour = (struct stack *)calloc(1, sizeof(struct stack))))
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
                    puts("Retry enter\n");
                    system("pause>0");
                    return;
                }
                temp[k] = c;
                k++;
            }
            if(feof(textFile))
                break;
            temp[k] = '\0';

            newTour->data.name = temp;

            if(!(fscanf(textFile, "%d", &k)))
            {
                printf("Retry input please");
                system("pause>0");
                *toursList = NULL;
                return;
            }
            newTour->data.cost = k;

            if(!(fscanf(textFile, "%d", &k)))
            {
                printf("Retry input please");
                system("pause>0");
                *toursList = NULL;
                return;
            }
            newTour->data.indicator = k;

            if(newTour->data.indicator == 1)
            {
                fseek(textFile, 1, SEEK_CUR);
                for(k = 0; k < 8; k++)
                {
                    fscanf(textFile, "%c", &c);
                    if(c < '0' || c > '9')
                    {
                        printf("Retry input please");
                        system("pause>0");
                        *toursList = NULL;
                        return;
                    }
                    newTour->data.info.date[k] = c;
                }
            }
            if(newTour->data.indicator == 2)
            {
                fscanf(textFile, "%d", &k);
                newTour->data.info.duration = k;
            }

            if(toursList == NULL)
                *toursList = newTour;
            else
            {
                newTour->next = *toursList;
                *toursList = newTour;
            }

            while(1)
            {
                fscanf(textFile, "%c", &c);
                if((c < 'A' || c > 'Z') && (c < 'a' || c > 'z'))
                    break;
            }
        }
        fclose(textFile);
    }
    else if(choise == 2)
    {
        printf("Enter file name\n>>> ");
        char *binName;
        binName = getFileName(2);

        if(!(binaryFile = fopen(binName, "rb")))
        {
            printf("Can't open file");
            system("pause>0");
            return;
        }

        struct stack *newTour;

        while(1)
        {

            if(!(newTour = (struct stack *)calloc(1, sizeof(struct stack))))
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
                fread(&c, sizeof(char), 1, binaryFile);

                if(feof(binaryFile))
                    break;

                if((c < 'A' || c > 'Z')&&(c < 'a' || c > 'z'))
                    break;

                if (!(temp = (char*)realloc(temp, (k + 2) * sizeof(char))))
                {
                    puts("Retry enter\n");
                    return;
                }
                temp[k] = c;
                k++;
            }

            if(feof(binaryFile))
                break;

            temp[k] = '\0';

            newTour->data.name = temp;

            fseek(binaryFile, -1, SEEK_CUR);

            if(!(fread(&k, sizeof(int), 1, binaryFile)))
            {
                printf("Retry input please");
                system("pause>0");
                *toursList = NULL;
                return;
            }
            newTour->data.cost = k;

            if((fread(&k, sizeof(int), 1, binaryFile))!= 1)
            {
                printf("Retry input please");
                *toursList = NULL;
                system("pause>0");
                return;
            }
            newTour->data.indicator = k;

            if(newTour->data.indicator == 1)
            {
                for(k = 0; k < 8; k++)
                {
                    fread(&c, sizeof(char), 1, binaryFile);
                    if(c < '0' || c > '9')
                    {
                        printf("Retry input please");
                        *toursList = NULL;
                        system("pause>0");
                        return;
                    }
                    newTour->data.info.date[k] = c;
                }
                newTour->data.info.date[9] = '\0';
            }
            if(newTour->data.indicator == 2)
            {
                fread(&k, sizeof(int), 1, binaryFile);
                newTour->data.info.duration = k;
            }
            if(!(feof(binaryFile)))
                fseek(binaryFile, 1, SEEK_CUR);

            if(toursList == NULL)
                *toursList = newTour;
            else
            {
                newTour->next = *toursList;
                *toursList = newTour;
            }
        }
        fclose(binaryFile);
    }

    puts("Stack loaded successfully");
    system("pause>0");
}

void addElement(struct stack **tourList)
{
    system("cls");
    struct stack *newTour = NULL;

    int choise;
    do
    {
        system("cls");
        puts("What do you want to enter?");
        puts("1 - enter by date's");
        puts("2 - enter by duration's");
        printf("0 - to exit\n>>> ");
        choise = check();
    }while(choise < 0 || choise > 2);

    system("cls");

    if(choise == 0)
        return;

    int much;
    printf("\nNow much tour's you want to enter?\n>>> ");
    much = check();
    system("cls");

    switch(choise)
    {
        case 1:
        {
            for(int i = 0; i < much; i++)
            {
                if(!(newTour = (struct stack *)calloc(1, sizeof(struct stack))))
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
                    printf("Enter tour date in format ddmmyyyy: ");
                    rewind(stdin);
                }while(!getDigits(newTour));

                newTour->data.indicator = 1;

                if(tourList == NULL)
                    *tourList = newTour;
                else
                {
                    newTour->next = *tourList;
                    *tourList = newTour;
                }
            }
            break;
        }
        case 2:
        {
            for(int i = 0; i < much; i++)
            {
                if(!(newTour = (struct stack *)calloc(1, sizeof(struct stack))))
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

                if(tourList == NULL)
                    *tourList = newTour;
                else
                {
                    newTour->next = *tourList;
                    *tourList = newTour;
                }
            }
            break;
        }
    }
}

void output(struct stack *tourList)
{
    int sizeCost = findmax(tourList, 2);
    int sizeName = findmax(tourList, 1);
    int sizeDate = findmax(tourList, 3);
    int sizeDuration = findmax(tourList, 4);
    int allSize = sizeCost + sizeDate + sizeDuration + sizeName;
    system("cls");
    if(tourList == NULL)
    {
        printf("Tour's not enrolled\n");
        system("pause>0");
        system("cls");
        return;
    }
    else
    {
        struct stack *tour = tourList;
        int i;

        outputHead(tour);

        while(tour)
        {
            outputOne(tour, i, sizeName);
            tour = tour->next;
            i++;
        }
    }
    for(int i = 0; i < allSize + 11; i++)
        printf("-");
}

void outputHead(struct stack *toursList)
{
    int sizeName = findmax(toursList, 1);
    int sizeCost = findmax(toursList, 2);
    int sizeDate = findmax(toursList, 3) + 2;
    int sizeDuration = findmax(toursList, 4);

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

void outputOne(struct stack *tour, int i, int sizeName)
{
    int sizeCost = findmax(tour, 2);
    int sizeDate = findmax(tour, 3);
    int sizeDuration = findmax(tour, 4);
    int allSize = sizeName + sizeCost + sizeDate + sizeDuration;
    for(int i = 0; i < allSize + 11; i++)
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

int findmax (struct stack *toursList, int code)
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

int menu()
{
    puts("\nEnter: ");
	puts("1) Add tour's");
	puts("2) Save tour's in file");
	puts("3) Show tour's");
	puts("4) Search tour's");
	puts("5) Delete tour's");
    puts("0) Close program");
    printf(">>> ");
	int x;
	x = check();
	return x;
}

int check()
{
    char y;
    int x;
    while (scanf("%d%c", &x, &y) != 2 || y != '\n' || x < 0 || x > 214748364)
    {
        rewind(stdin);
        puts("\nPlease, enter correct format: ");
    }
    return x;
}

int getDigits(struct stack *tourList)
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

    for(int i = 0; i < 9; i++)
        tourList->data.info.date[i] = temp[i];
    return 1;
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

void search(struct stack *toursList)
{
    system("cls");
    if(toursList == NULL)
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
            struct stack *tour = toursList;
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
            int sizeName = findmax(toursList, 1);
            switch(choise)
            {
                case 1:
                {
                    system("cls");
                    printf("\nEnter name to find\n>>> ");
                    find = getString();
                    uppercase(find);
                    int length = findmax(tour, 1);
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
                    temp = (char *)malloc(9*sizeof(char));
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

void delete(struct stack **toursList)
{
    system("cls");
    if(toursList == NULL)
    {
        printf("\nTour's not enrolled\n");
        system("pause>0");
        system("cls");
        return;
    }

    else
    {
        do
        {
            struct stack *tour = *toursList;
            struct stack *preTour = NULL;

            int choise, num = 0;

            output(tour);

            if(tour == NULL)
                return;

            do
            {
                puts("\nEnter 0 to end delete process");
                printf("Enter number to delete\n>>> ");
                choise = check();
            }while(choise < 0);

            if(choise == 0)
                return;

            num = 0;
            tour = *toursList;

            while(tour != NULL)
            {
                if(num == (choise - 1))
                {
                    if(tour == *toursList)
                    {
                        *toursList = tour->next;
                        free(tour);
                        tour->next = NULL;
                    }
                    else
                    {
                        preTour->next = tour->next;
                        free(tour);
                        tour->next = NULL;
                    }
                }
                num++;
                preTour = tour;
                tour = tour->next;
            }
        }while(1);
    }
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

        if (!(temp = (char*)realloc(temp, (k + 4) * sizeof(char))))
        {
            rewind(stdin);
            puts("Retry enter\n");
            return NULL;
        }
        temp[k] = c;
    }
    if(code == 1)
        strcat(temp, ".txt");
    if(code == 2)
        strcat(temp, ".bin");


    return temp;
}

// С функцией помог Андрей Сикорин
void reverseStack(struct stack **head)
{
    struct stack *temp = *head;
    struct stack *preHead = *head;

    // Set head on the bot of the stack
    while (temp)
    {
        if (temp->next == NULL)
            *head = temp;
        temp = temp->next;
    }

    struct stack *reverseStack = *head;

    while (1)
    {
        temp = preHead;
        while (1)
        {
            if (temp->next == reverseStack)
            {
                reverseStack->next = temp;
                reverseStack = reverseStack->next;
                break;
            }
            temp = temp->next;
        }
        if (reverseStack == preHead)
        {
            reverseStack->next = NULL;
            break;
        }
    }
}

