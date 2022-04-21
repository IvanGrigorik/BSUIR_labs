#include <stdio.h>
#include <stdlib.h>
#include <io.h>

// Из текстового файла добавлять и упорядочивать слова в дерево

typedef struct tree
{
    char *info;
    struct tree *left;
    struct tree *right;
}tree;

int main()
{
    FILE *f;
    f = fopen("file.txt", "r+");
    char *tempString = NULL;

    tree *node = NULL;

    while(1)
    {
        fscanf(f, "%s", tempString);

        if(feof(f))
            break;

        if(node == NULL)
        {
            node = (struct tree *)malloc(sizeof(struct tree));
            node->info = tempString;
            continue;
        }
        while(node != NULL)
        {
            if(strcmp(node->info, tempString) == 0)
                break;

            if(strcmp(node->info, tempString) > 0)
                node = node->left;
            else
                node = node->right;
        }
        node = (struct tree *)malloc(sizeof(struct tree));
        node->info = tempString;
        node->left = NULL;
        node->right = NULL;
    }
}