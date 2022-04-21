#include <stdio.h>
#include <stdlib.h>
#include <io.h>

// Разработать программу "библиотека"
// Должны работать функции добавления и сортировка
// Структура: автор, название, год

typedef struct book
{
    char bookName[20];
    char author[20];
    int year;
}book;

typedef struct library
{
    book *bookList;
    int amount;
}library;

int menu();
void add (library *newBooks);
void sortYear(library *books);
void show(library library1);

int main()
{
    library newLibrary;
    newLibrary.bookList = NULL;
    newLibrary.amount = 0;

    while(1) {
        switch (menu()) {
            case 1:
                add(&newLibrary);
                break;

            case 2:
                sortYear(&newLibrary);
                break;

            case 3:
                show(newLibrary);
                break;

            case 0:
                return 0;
        }
    }
}

void show(library library1)
{
    system("cls");
    for(int i = 0; i < library1.amount; i++)
    {
        printf("%d", library1.bookList[i].year);
        puts(library1.bookList[i].bookName);
        puts(library1.bookList[i].author);
    }
}

void add(library *newBooks)
{
    // Считываем, сколько новых книг хотим ввести.
    int x;
    scanf("%d", &x);
    newBooks->amount += x;

    book *temp = (book *)realloc(newBooks->bookList, newBooks->amount * sizeof(book));
    newBooks->bookList = temp;

    for(int i = newBooks->amount - x; i < newBooks->amount; ++i)
    {
        system("cls");
        scanf("%d", &newBooks->bookList[i].year);
        scanf("%s", newBooks->bookList[i].author);
        scanf("%s", newBooks->bookList[i].bookName);
    }
    return;
}

void swap(book *n1, book *n2)
{
    book temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

void sortYear(library *books)
{
    for(int i = 0; i < books->amount; i++)
        for(int j = i + 1; j < books->amount; j++)
            if(books->bookList[i].year > books->bookList[j].year)
                swap(&books->bookList[i], &books->bookList[j]);
}

int menu()
{
    int x;
    puts("1) Enter new book");
    puts("2) Sort book's");
    puts("0) Exit");
    scanf("%d", &x);
    return x;

}