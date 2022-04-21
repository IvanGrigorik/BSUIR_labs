#include <stdio.h>
#include <io.h>

// Дана однонаправленная очередь, упорядоченная по убыванию.
// Записать её в бинарный файл, имя которого задаётся в командной строке,
// по возрастанию, без доп. файлов и массивов.

typedef struct queue
{
    int info;
    struct queue *next;
}queue;

void putQueueInToFile(FILE *f, queue *head);

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 1;

    char *fileName = strcat(argv[1], ".bin");
    FILE *f = fopen(fileName, "w+");

    queue *head = NULL;
    putQueueInToFile(f, head);
}

void putQueueInToFile(FILE *f, queue *head)
{
    rewind(f);

    int temp;
    fpos_t posTemp;

    fwrite(&head->info, sizeof(int), 1, f);
    head = head->next;

    while(head)
    {
        /*
         * Функция освобождения первой позиции в файле
         * Принцип работы - пока позиция не будет равна первой,
         * мы будем записывать числа на следующую позицию
         */
        fseek(f, -sizeof(int), SEEK_END);
        do
        {
            fgetpos(f, &posTemp);

            fread(&temp, sizeof(int), 1, f);
            fseek(f, 1, SEEK_CUR);
            fwrite(&temp, sizeof(int), 1, f);

            posTemp -= (sizeof(int) + 1);
            fsetpos(f, &posTemp);

        }while(posTemp > 0);

        rewind(f);
        fwrite(&head->info, sizeof(int), 1, f);
        head = head->next;
    }

}