//Created by SiFi
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool check(char* firstWord, char* lastWord)
{
for (int i = 0; ; ++i)
{
if ((firstWord[i] != '\0' && firstWord[i] != ' ') && (lastWord[i] == '\0' || lastWord[i] == ' ')) return true;
if ((firstWord[i] == '\0' || firstWord[i] == ' ') && (lastWord[i] != '\0' && lastWord[i] != ' ')) return false;
if (firstWord[i] < lastWord[i]) return false;
if (firstWord[i] > lastWord[i]) return true;
}
}

void reverse(char* left, char* right)
{
for ( ; left < right; left++, right--)
{
char temp = *left;
*left = *right;
*right = temp;
}
}

int main()
{
char str[] = "do you know the way why are you gay aaaaaa";
puts(str);
int n = sizeof(str);
for (int i = 0; i < n; ++i)
{
    while (str[i] == ' ')
    i++;
    char* firstWordStart = &str[i];
    while (str[i] != ' ' && str[i] != '\0')
    i++;
    char* firstWordEnd = &str[i - 1];
    for (int j = i; j < n; ++j)
    {
        while (str[j] == ' ')
        j++;
        char* lastWordStart = &str[j];
        while (str[j] != ' ' && str[j] != '\0')
        j++;
        char* lastWordEnd = &str[j-1];
        if (check(firstWordStart, lastWordStart))
        {
            reverse(firstWordStart, firstWordEnd);
            reverse(lastWordStart, lastWordEnd);
            reverse(firstWordEnd, lastWordStart - 1);
            reverse(firstWordStart, lastWordEnd);
            firstWordEnd = firstWordStart + (lastWordEnd - lastWordStart);
        }
    }
}
puts(str);
return 0;
}
