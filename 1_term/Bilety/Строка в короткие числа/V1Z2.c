//Created by SiFi
#include <stdio.h>
#include <stdlib.h>

int main ()
{

    int length;
    short *array;
    char *string;

    printf("Enter length\n");
    scanf("%d", &length);

    array = (short*)calloc(length, sizeof(short));
    string = (char*)malloc((length + 1) * sizeof(char));

    printf("Enter string\n");
    rewind(stdin);
    fgets(string, length, stdin);
    printf("Your string\n");
    puts(string);

    chartoint(string, array);

    printf("Your array\n");
    for (int i = 0; i < length; i++) {
        printf("%hd ", array[i]);
    }
    return 0;
}

int chartoint(char *str, short *arr)
{
    int i = 0, znak = 1, razr = 0, j = 0;

    for(i = 0; str[i]; i++){
        if (str[i] == '-') znak = -1;
        if(str[i]>= '0' && str[i] <= '9')
            razr = 10 * razr + (str[i] - '0');
        if(str[i] == ' ' || str[i] == '\0')
        {arr[j] = (znak * razr);
         razr = 0;
         znak = 1;
         j++;}}
    return arr[j] = (znak * razr);}
