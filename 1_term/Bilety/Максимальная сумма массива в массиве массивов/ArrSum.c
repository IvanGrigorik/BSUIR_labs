//Created by SiFi

int function(int arraysNumber, int *array, int arraySize, ...)
{
    int *pointer1 = &arraySize;
    int **pointer2 = &array;
    int maxSum = 0, sum, i;
    while (arraysNumber--)
    {sum = 0;
    for (i = 0; i < *pointer1; i++)
    sum += *(*pointer2 + i);
    if (maxSum < sum)
            maxSum = sum;
        pointer2 += 2;
        pointer1 += 2;
    }
    return maxSum;
}
