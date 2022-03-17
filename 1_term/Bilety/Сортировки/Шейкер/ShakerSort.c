//Created by SiFi

//ф-ция для обмена значений ячеек
void swapEl(int *arr, int i)
{
 int buff;
 buff = arr[i];
 arr[i] = arr[i - 1];
 arr[i - 1] = buff;
}

//ф-ция "шейкер"-сортировки
void myShakerSort(int *arr, int size)
{
 int leftMark = 1;
 int rightMark = size - 1;
 while (leftMark <= rightMark)
 {
 for (int i = rightMark; i >= leftMark; i--)
    if (arr[i - 1] > arr[i]) swapEl(arr, i);
        leftMark++;


 for (int i = leftMark; i <= rightMark; i++)
    if (arr[i - 1] > arr[i]) swapEl(arr, i);
        rightMark--;
 }
}
