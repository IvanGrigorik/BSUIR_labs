#include <stdio.h>

struct tree{
    int info;
    struct tree *left;
    struct tree *right;
};

void output(struct tree *root)
{
    if(root->left)
        output(root->left);
    printf("%d", root->info);
    if(root->right)
        output(root->right);
}
