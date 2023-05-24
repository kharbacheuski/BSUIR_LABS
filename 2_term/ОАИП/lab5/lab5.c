#include <stdio.h>
#include <stdlib.h>


struct Node
{
    int time;
    char filename[100];
    struct Node* left;
    struct Node* right;
};

struct Node* arr;
int fr = 0;

struct Node** forD[100];
int fdi = 0;

void PrintNode(struct Node* curr)
{
    /*
    char* lt = ((curr->left != NULL) ? curr->left->filename : "null");
    char*  rt = ((curr->right != NULL) ? curr->right->filename : "null");
    printf("%s <- %s -> %s\n", lt, curr->filename, rt);
    */
    
    int lt = ((curr->left != NULL) ? curr->left->time : -1);
    int  rt = ((curr->right != NULL) ? curr->right->time : -1);
    printf("%d <- %d -> %d\n", lt, curr->time, rt);
    
}

int Walk(struct Node** arr)
{
    if (*arr == NULL)
        return 1; // three is clear
        
    PrintNode(*arr);
    if ((*arr)->left == NULL && (*arr)->right == NULL)
        return 0;
    if ((*arr)->left != NULL)
        Walk(&(*arr)->left);
    if ((*arr)->right != NULL)
        Walk(&(*arr)->right);
}

void Algorithm(struct Node nd)
{
    return nd.time < 3000 ? 1 : 0;
}

struct Node** Search(struct Node** arr, int(*alg)(struct Node))
{
    if (*arr == NULL)
        return NULL;

    if (alg != NULL && alg(**arr) == 1)
        return arr;

    if ((*arr)->left == NULL && (*arr)->right == NULL)
        return NULL;
    if ((*arr)->left != NULL)
        return Search(&(*arr)->left, alg);
    if ((*arr)->right != NULL)
        return Search(&(*arr)->right, alg);
}

void Add(struct Node item)
{
    struct Node* curr = arr;
    arr[fr].time = item.time;
    strcpy(arr[fr].filename, item.filename);
    while (1)
    {
        int isBigger = (item.time >= curr->time) ? 1 : 0;
        if (isBigger)
        {
            //right
            if (curr->right == NULL)
            {
                curr->right = arr + fr;
                break;
            }
            else
            {
                curr = curr->right;
                continue;
            }
        }
        else
        {
            // left
            if (curr->left == NULL)
            {
                curr->left = arr + fr;
                break;
            }
            else
            {
                curr = curr->left;
                continue;
            }
        }
    }
    fr++;
    //PrintNode(curr);
}

void Delete(struct Node** item)
{
    // no child
    if ((*item)->right == NULL && (*item)->left == NULL)
    {
        *item = NULL;
        return;
    }

    // one child
    if ((*item)->right != NULL && (*item)->left == NULL)
    {
        *item = (*item)->right;
        return;
    }
    if ((*item)->left != NULL && (*item)->right == NULL)
    {
        *item = (*item)->left;
        return;
    }

    // two child
    if ((*item)->right->left == NULL)
    {
        (*item)->time = (*item)->right->time;
        strcpy((*item)->filename,(*item)->right->filename);
        Delete(&(*item)->right);
    }
    else
    {
        struct Node** curr = &(*item)->right;
        while (1)
        {
            if ((*curr)->left == NULL)
            {
                (*item)->time = (*curr)->time;
                strcpy((*item)->filename, (*curr)->filename);
                Delete(curr);
                break;
            }
            curr = &((*curr)->left);
        }
    }
}


int main()
{
    arr = (struct Node*) malloc(100 * sizeof(struct Node));
    for (int i = 0; i < 100; i++) 
        arr[i].left = arr[i].right = NULL;
    arr[0].time = 1000;
    strcpy(arr[0].filename, "root");
    fr++;

    struct Node p, x, c, v, b, n, g;
    p.time = 500;
    gets(p.filename);
    x.time = 1500;
    gets(x.filename);
    c.time = 750;
    gets(c.filename);
    v.time = 879;
    gets(v.filename);
    b.time = 315;
    gets(b.filename);
    n.time = 2390;
    gets(n.filename);
    g.time = 650;
    gets(g.filename);

    Add(p);
    Add(x);
    Add(c);
    Add(v);
    Add(b);
    Add(n);
    Add(g);
    printf("\n");

    Walk(&arr);
    printf("\nafter delete\n");
    while (1)
    {
        struct Node** del = Search(&arr, Algorithm);
        if (del == NULL)
            break;
        Delete(del);
    }

    if(Walk(&arr))
        printf("clear\n");

    free(arr);
    return 0;
}
