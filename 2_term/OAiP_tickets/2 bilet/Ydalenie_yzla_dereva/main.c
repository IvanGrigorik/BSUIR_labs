#include <stdio.h>

struct tree{
    int info;
    struct tree *left;
    struct tree *right;
};

void delete(struct tree **node, int del)
{
    if(node != NULL)
    {
        if((*node)->info == del)
        {
            struct tree *delNode = *node;

            if((*node)->right == NULL && (*node)->left == NULL) {
                free(*node);
                node = NULL;
            }
            if((*node)->left == NULL)
                *node = delNode->right;
            if((*node)->right == NULL)
                *node = delNode->left;

            else
            {
                *node = delNode->right;

                struct tree **newNode = node;
                while(*newNode)
                    newNode = &((*newNode)->left);

                *newNode = delNode->left;
            }
        }
        else
        {
            if((*node)->info < del)
                delete(&((*node)->right), del);
            if((*node)->info < del)
                delete(&(*node)->left), del);
        }
    }
}

int main()
{
    struct tree *root;
    int delElement;
    scanf("%d", &delElement);
    delete(&root, delElement);
}
