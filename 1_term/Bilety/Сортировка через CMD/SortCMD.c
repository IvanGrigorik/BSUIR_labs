//Created not by SiFi
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
bool compare(char* word1, char* word2)
{
    int i = 0;
    while (true)
    {
        if (word1[i] == '\0' && word2[i] != '\0') return false;
        else if (word2[i] == '\0' && word1[i] != '\0') return true;
        if (word1[i] < word2[i]) return false;
        if (word2[i] < word1[i]) return true;
        i++;
    }
}

int main(int n, char **str)
{
    for (int i = 1; i < n; ++i)
    printf("%s\t", str[i]);
    puts("");
    for (int i = 1; i < n - 1; ++i)
        for (int j = n - 1; j > i ; --j)
            if (compare(str[j-1], str[j]))
            {
                char *temp = str[j];
                str[j] = str[j-1];
                str[j-1] = temp;
            }
    for (int i = 1; i < n; ++i)
    printf("%s ", str[i]);
    return 0;
}
