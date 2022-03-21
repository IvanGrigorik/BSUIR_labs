#include <stdio.h>
#include <stdlib.h>

void vstavka();
void otbor();
void shell();
void bubble();
void shaker();
void hoar();

int main(void)
{
    int n = 13;
    int arr1[n], arr2[n], arr3[n], arr4[n], arr5[n], arr6[n];


    puts("arr1:");
    for (int i = 0; i < n; ++i)
        printf("%4i", arr1[i] = 1 + (rand() % 20));
    puts("");
    vstavka(arr1, n);
    for (int i = 0; i < n; ++i)
        printf("%4i", arr1[i]);
    puts("");


    puts("arr2:");
    for (int i = 0; i < n; ++i)
        printf("%4i", arr2[i] = 1 + (rand() % 20));
    puts("");
    otbor(arr2, n);
    for (int i = 0; i < n; ++i)
        printf("%4i", arr2[i]);
    puts("");


    puts("arr3:");
    for (int i = 0; i < n; ++i)
        printf("%4i", arr3[i] = 1 + (rand() % 20));
    puts("");
    shell(arr3, n);
    for (int i = 0; i < n; ++i)
        printf("%4i", arr3[i]);
    puts("");


    puts("arr4:");
    for (int i = 0; i < n; ++i)
        printf("%4i", arr4[i] = 1 + (rand() % 20));
    puts("");
    bubble(arr4, n);
    for (int i = 0; i < n; ++i)
        printf("%4i", arr4[i]);
    puts("");


    puts("arr5:");
    for (int i = 0; i < n; ++i)
        printf("%4i", arr5[i] = 1 + (rand() % 20));
    puts("");
    shaker(arr5, n);
    for (int i = 0; i < n; ++i)
        printf("%4i", arr5[i]);
    puts("");

    
    puts("arr6:");
    for (int i = 0; i < n; ++i)
        printf("%4i", arr6[i] = 1 + (rand() % 20));
    puts("");
    hoar(arr6, 0, n - 1);
    for (int i = 0; i < n; ++i)
        printf("%4i", arr6[i]);
    puts("");
    return 0;
}

void vstavka(int arr[], int n)
{
    for (int i = 1; i < n; ++i)
        for (int j = i; j && arr[j] < arr[j-1]; --j)
        {
            int temp = arr[j];
            arr[j] = arr[j-1];
            arr[j-1] = temp;
        }
}

void otbor(int arr[], int n)
{
    for (int i = 0; i < n - 1; ++i)
        for (int j = i + 1; j < n; ++j)
            if (arr[i] > arr[j])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
}

void shell(int arr[], int n)
{
    for (int step = n / 2; step; step /= 2)
        for (int i = step; i < n; ++i)
            for (int j = i - step; j >= 0 && arr[j] > arr[j+step]; j -= step)
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
}

void bubble(int arr[], int n)
{
    for (int i = 0; i < n - 1; ++i)
        for (int j = n - 1; j > i; --j)
            if (arr[j] < arr[j-1])
            {
                int temp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = temp;
            }
}

void shaker(int arr[], int n)
{
    int left = 0, right = n - 1;
    char flag = 't';
    while(right > left && flag)
    {
        flag = '\0';
        for (int i = left; i < right; ++i)
            if (arr[i] > arr[i+1])
            {
                int temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
                flag = 't';
            }
        right--;
        for (int i = right; i > left; --i)
            if (arr[i] < arr[i-1])
            {
                int temp = arr[i];
                arr[i] = arr[i-1];
                arr[i-1] = temp;
                flag = 't';
            }
        left++;
    }
}

void hoar(int* arr, int left, int right)
{
    int pivot = arr[(left + right) / 2];
    int stepLeft = left;
    int stepRight = right;
    do {
        while (arr[stepLeft] < pivot)
            stepLeft++;
        while (arr[stepRight] > pivot)
            stepRight--;
        if (stepLeft <= stepRight)
        {
            int temp = arr[stepLeft];
            arr[stepLeft] = arr[stepRight];
            arr[stepRight] = temp;
            stepLeft++;
            stepRight--;
        }
    } while (stepLeft <= stepRight);
    if (stepLeft < right)
        hoar(arr, stepLeft, right);
    if (stepRight > left)
        hoar(arr, left, stepRight);
}


