//Created by SiFi
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int size, i = 0, j = 0;
    scanf("%d", &size);
    char *str;
    str = (char*)calloc(size + 1, sizeof(char));
    rewind(stdin);
    fgets(str, size+1, stdin);

    while(str[i] != '\0')
    {
        while(str[i] == ' ')
            i++;
        while(str[i] >= 'A' && str[i]<='Z')
        {
            i++;
            j++;
        }

        while(str[i] >= 'a' && str[i]<='z')
        {
            i++;
            j++;
        }
        i++;
    }

    printf("%d", j);
    return 0;
}
