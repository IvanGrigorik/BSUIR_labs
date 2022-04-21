#include <stdio.h>

// Дан массив структур, содержащих указатели на две структуры
// 1-я - имя студента и его группа, 2-я - 4 оценки.
// Найти студента с наибольшим баллом

typedef struct info
{
    char name[20];
    char group[15];
}info;

typedef struct max
{
    int g1;
    int g2;
    int g3;
    int g4;
}max;

typedef struct student
{
    info *information;
    max *grades;
}student;

void findMax(student *list, int arrSize)
{
    unsigned int maxSum = 0, sum;
    student maxStudent;

    for(int i = 0; i < arrSize; i++)
    {
        sum = list[i].grades->g1+list[i].grades->g2+list[i].grades->g3+list[i].grades->g4;
        if(sum > maxSum)
        {
            maxSum = sum;
            maxStudent = list[i];
        }
    }
    printf("%d", maxSum);
    puts(maxStudent.information->group);
    puts(maxStudent.information->name);
}