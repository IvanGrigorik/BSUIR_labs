//
// Created by Ivan on 20.05.2021.
//

#include "fun.h"

int isEmpty(struct tree *node)
{

    if (node == NULL)
    {
        puts("\nTree are no element's on the tree");
        return 0;
    }

    return 1;
}

int check() {
    char y;
    int x;
    while (scanf("%d%c", &x, &y) != 2 || y != '\n' || x < 0)
    {
        rewind(stdin);
        puts("\nPlease, enter correct format: ");
    }
    return x;
}

char *getString(char newWord[])
{
    char c;
    int k;
    rewind(stdin);

    for(k = 0; (c = (char)getchar()) != '\n' && k < ARRAY_SIZE; k++)
    {
        if((c < 'A' || c > 'Z') && (c < 'a' || c > 'z'))
        {
            printf("\nPlease, enter right format \n>>> ");
            rewind(stdin);
            return NULL;
        }
        newWord[k] = c;
    }
    newWord[k] = '\0';
    return newWord;
}

struct tree *getMemory(struct information value)
{
    struct tree *newElement = (struct tree *)malloc(sizeof(struct tree));
    newElement->left = newElement->right = NULL;
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        newElement->element.englishWord[i] = value.englishWord[i];
        newElement->element.russianWord[i] = value.russianWord[i];
    }
    return newElement;
}

void insert(struct tree **head, struct information value)
{
    if (*head == NULL)
    {
        *head = getMemory(value);
        return;
    }

    struct tree *newInfo = *head;

    while (newInfo) {
        if (strcmp(value.englishWord, newInfo->element.englishWord) == 0)
            return;
        if (strcmp(value.englishWord, newInfo->element.englishWord) > 0) {
            if (newInfo->right) {
                newInfo = newInfo->right;
                continue;
            } else {
                newInfo->right = getMemory(value);
                return;
            }
        } else if (strcmp(newInfo->element.englishWord, value.englishWord) > 0) {
            if (newInfo->left) {
                newInfo = newInfo->left;
                continue;
            } else {
                newInfo->left = getMemory(value);
                return;
            }
        }
        else
        {
            puts("Error");
            system("pause>0");
            exit(1);
        }
    }
}

void input(struct tree **head)
{
    system("cls");
    puts("\nHow many elements do you want to enter?");
    puts("Enter 0 to exit");
    int much, i;
    much = check();

    struct information newInfo;
    for (i = 0; i < much; i++)
    {
        printf("\n%d element:\n", i+1);

        do
        {
            printf("English word: ");
        }while(!(getString(newInfo.englishWord)));

        rewind(stdin);
        printf("Russian word: ");
        gets(newInfo.russianWord);

        insert(head, newInfo);
    }
}

void show(struct tree *obitoRoot)
{
    if (!isEmpty(obitoRoot))
        return;
    printf("\n%s - %s\n", obitoRoot->element.englishWord, obitoRoot->element.russianWord);
    if (obitoRoot->left)
        show(obitoRoot->left);
    if (obitoRoot->right)
        show(obitoRoot->right);
}

void showTreeByStack(struct tree *node)
{
    system("cls");
    if (!isEmpty(node))
        return;
    struct stack
    {
        struct tree *node;
        struct stack *prev;
    } *stack = NULL, *prevElement = NULL;

    int goLeft = 1;

    stack = (struct stack*)calloc(1, sizeof(struct stack));

    stack->node = node;
    stack->prev = prevElement;
    printf("\n%s - %s\n", node->element.englishWord, node->element.russianWord);

    while (node->right || stack)
    {
        // While element is not leaf.
        do
        {
            if (goLeft && node->left)
                node = node->left;
            else if (node->right)
                node = node->right;
            goLeft = 1;

            if (node->left && node->right)
            {
                prevElement = stack;
                stack = (struct stack *)calloc(1, sizeof(struct stack));
                stack->node = node;
                stack->prev = prevElement;
            }
            printf("\n%s - %s\n", node->element.englishWord, node->element.russianWord);
        } while(node->left || node->right);

        if (stack)
        {
            node = stack->node;
            prevElement = stack->prev;
            free(stack);
        }

        stack = prevElement;

        if (node->left && node->right)
            goLeft = 0;
        else
            break;
    }
    system("pause>0");
}

void deleteAll(struct tree **root)
{
    if (!isEmpty(*root))
        return;
    if ((*root)->left)
        deleteAll(&((*root)->left));
    if ((*root)->right)
        deleteAll(&((*root)->right));
    free(*root);
    *root = NULL;
}

void deleteNode(struct tree **node, char *searchWord)
{
    if ((*node) != NULL)
    {
        if ((strcmp((*node)->element.englishWord, searchWord)) == 0)
        {
            struct tree *delNode = *node;

            if ((*node)->left == NULL && (*node)->right == NULL)
                *node = NULL;
            else if ((*node)->left == NULL)
                *node = delNode->right;
            else if ((*node)->right == NULL)
                *node = delNode->left;
            else
            {
                *node = delNode->right;
                struct tree **newNode = node;

                while (*newNode != NULL)
                    newNode = &((*newNode)->left);
                *newNode = delNode->left;
            }
            free(delNode);
            return;
        }
        else
        {
            if((strcmp((*node)->element.englishWord, searchWord)) > 0)
                deleteNode(&((*node)->left), searchWord);
            if((strcmp((*node)->element.englishWord, searchWord)) < 0)
                deleteNode(&((*node)->right), searchWord);
        }
    }
    return;
}

void delete(struct tree **node)
{
    system("cls");
    if (!isEmpty(*node))
        return;
    printf("Enter english element to delete\n>>> ");
    char stringToSearch[ARRAY_SIZE], *ptrStringToSearch;
    gets(stringToSearch);
    ptrStringToSearch = &stringToSearch[0];

    // Получили все данные и спокойно удаляем
    deleteNode(node, ptrStringToSearch);
    puts("Deletion process is complete");
    system("pause>0");
    return;
}

int menu()
{
    system("cls");
    puts("\nEnter: ");
    puts("1) Add word's");
    puts("2) Show vocabulary recursively");
    puts("3) Show vocabulary non-recursively");
    puts("4) Show tree pseudo-graphically");
    puts("5) Delete word");
    puts("6) Delete vocabulary");
    puts("0) Close program");
    printf(">>> ");
    int x;
    x = check();
    return x;
}

void print(struct tree* root, int level)
{
    if (root)
        print(root->right, level + 1);
    for (int n = 0; n<level; ++n)
        printf("           ");
    if (root)
        printf("%s - %s", root->element.englishWord, root->element.russianWord);
    else
        printf("\n");
    if (root)
        print(root->left, level + 1);
}

int height (struct tree *node)
{
    if (node != NULL)
    {
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }
    return 0;
}

int difference (struct tree *node)
{
    return height(node->left) - height(node->right);
}

struct tree *leftLeftRotation (struct tree *node)
{
    struct tree *temp;
    temp = node->left;
    node->left = temp->right;
    temp->right = node;

    return temp;
}

struct tree *rightRightRotation (struct tree *node)
{
    struct tree *temp;
    temp = node->right;
    node->right = temp->left;
    temp->left = node;

    return temp;
}

struct tree *leftRightRotation (struct tree *node)
{
    struct tree *temp;
    temp = node->left;
    node->left = rightRightRotation(temp);

    return leftLeftRotation(node);
}

struct tree *rightLeftRotation (struct tree *node)
{
    struct tree *temp;
    temp = node->right;
    node->right = leftLeftRotation(temp);

    return rightRightRotation(node);
}

struct tree *balance (struct tree *temp)    // балансировка дерева
{
    int balanceFactor = difference(temp);

    if (balanceFactor > 1)
    {
        if ( difference(temp->left) > 0 )
            temp = leftLeftRotation(temp);
        else
            temp = leftRightRotation(temp);
    }
    else if (balanceFactor < -1)
    {
        if ( difference(temp->right) > 0 )
            temp = rightLeftRotation(temp);
        else
            temp = rightRightRotation(temp);
    }
    return temp;
}