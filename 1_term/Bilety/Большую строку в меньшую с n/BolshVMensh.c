//Created by SiFI
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int size, size2, i, j, n;
    char *str1, *str2;

    scanf("%d", &size);

    str1 = (char *)calloc(2 * size + 1, sizeof(char));
    str2 = (char *)calloc(2 * size + 1, sizeof(char));
    rewind(stdin);

    fgets(str1, size, stdin);
    puts(str1);
    fgets(str2, size, stdin);
    puts(str2);

    while(str2[i] == ' ')
        i++;
    int ns2 = i;
    while(str2[i] != '\0')
        i++;
    int ks2 = i - 1;
    i = 0;
    while(str1[i] == ' ')
        i++;
    int ns = i;
    while(str1[i] != '\0')
        i++;
    int ks = i - 1;
    int len1 = ks - ns;
    int len2 = ks2 - ns2;

    scanf("%d", &n);
    if(len2 < len1)
        strob(str2, str1, n, len2);

    else if(len1 <= len2)
        strob(str1, str2, n, len1);
    puts(str1);

    return 0;
}

void strob(char *str1, char *str2, int n, int size)
{
    for(int i = 0; i < size; i++)
        str1[n++] = str2[i]
}
void strob_2(char *str1, char *str2, int n, int size)
{
    int i;
    for(i = n; i < n + size; i++)
        str1[i] = str2[i - n];
}
