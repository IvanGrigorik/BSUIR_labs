//Created by SiFi

#include <stdio.h>
#include <stdlib.h>
#define SIZE 20
void sort(int* nums, int begin, int end)
{
    int l = begin, r = end;
    int v = nums[l+(r-l)/2];
    while(l <= r)
    {
        while(nums[l] < v) l++;
        while(nums[r] > v) r--;
        if(l <= r)
        {
            int tmp = nums[l];
            nums[l] = nums[r];
            nums[r] = tmp;
            l++, r--;
        }
    }
    if(begin < r)
        sort(nums, begin, r);
    if(l < end)
        sort(nums, l, end);
}

int main()
{
  int a[SIZE];
  // Заполнение массива случайными числами
  for (int i = 0; i<SIZE; i++)
    a[i] = rand() % 201 - 100;
  // Вывод элементов массива до сортировки
  for (int i = 0; i<SIZE; i++)
    printf("%4d ", a[i]);
  printf("\n");
  sort(a, 0, SIZE-1); // вызов функции сортировки
            // Вывод элементов массива после сортировки
  for (int i = 0; i<SIZE; i++)
    printf("%4d ", a[i]);
  printf("\n");
  getchar();
  return 0;
}
