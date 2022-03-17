//Created by SiFi
#include <stdio.h>
// Функция сортировки прямым выбором

void selectionSort(int *num, int size)
{
  int min, temp; // для поиска минимального элемента и для обмена
  for (int i = 0; i < size - 1; i++)
  {
    min = i;
    for (int j = i + 1; j < size; j++)
      if (num[j] < num[min]) min = j;
    temp = num[i];
    num[i] = num[min];
    num[min] = temp;
  }
}
