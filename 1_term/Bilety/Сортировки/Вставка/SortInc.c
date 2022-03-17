#define SIZE 8
#include <stdio.h>

int main()
{
    int num[] = {8, 5,1,4,6,123,321,123};

     for (int i = 1; i < SIZE; i++)
      {
        int value = num[i];
        int index = i;

        while ((index > 0) && (num[index - 1] > value))
        {
            for(int k = 0; k < SIZE; k++)
            printf("%d ", num[k]);
        puts("");
          num[index] = num[index - 1];
          index--;
        }
        num[index] = value;
      }
for(int k = 0; k < SIZE; k++)
            printf("%d ", num[k]);
        puts("");
}
