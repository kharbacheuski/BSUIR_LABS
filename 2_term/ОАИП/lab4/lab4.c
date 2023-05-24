#include <stdio.h>
#include <stdlib.h>

struct Node
{
    struct Node* next;
    int num;
};

// очередь
int qStart = 0;
int qEnd = 0;
struct Node* queue;

void queue_add(struct Node x)
{
    queue = (struct Node*) realloc(queue, sizeof(struct Node)*(qEnd - qStart + 1));
    queue[qEnd].next = x.next;
    queue[qEnd].num = x.num;
    qEnd++;
    printf("------\nqueue\n------\n");
    for (int i = qStart; i < qEnd; i++)
    {
        if (queue[i].next != NULL)
            printf("circle link\n");
        else
            printf("%d\n", queue[i].num);
    }
    printf("----------------------\n");
}

struct Node queue_pop()
{
    return queue[qStart++];
}

// кольцо
struct Node* circle;

void circle_add(struct Node nd)
{
    int len = 0;
    struct Node* last = circle;
    printf("------\ncircle\n------\n");
    while (1)
    {
        len++;
        printf("%s%d -> ", len==1?"root = ":"", last);
        if (last->next == circle)
        {
            circle[len].next = circle;
            circle[len].num = nd.num;
            last->next = &circle[len];
            printf("%d -> root\n", last->next);
            printf("--------------\n");
            break;
        }
        last = last->next;
    }

    printf("circle len is %d\n", len+1);
    return;
}

void remove_from_circle(int pos)
{
    if (pos == 1)
    {
        printf("cannot delete root item!\n");
        return;
    }
    int len = 0;
    struct Node* last = circle;

    while (1)
    {
        len++;
        if (last->next == circle)
        {
            printf("index out of range!\n");
            return;
        }
        if (len + 1 == pos)
        {
            last->next = (last->next)->next;
            return;
        }
        last = last->next;
    }
    return;
}

int main()
{
    // queue
    queue = (struct Node*)malloc(1 * sizeof(struct Node));
    circle = (struct Node*)malloc(10 * sizeof(struct Node));
    if (circle == NULL || queue == NULL)
        return 1;
    circle[0].next = circle;

    int num;
    char c;
    while (1)
    {
        printf("a - insert circle\nb - add to circle\nc - add to queue\nd - remove from circle(at index)");
        c = getchar();
        rewind(stdin);

        struct Node tmpNode;
        tmpNode.next = NULL;
        if (c == 'a')
        {
            tmpNode.next = circle;
            queue_add(tmpNode);
        }
        else if(c == 'b' || c == 'c')
        {
            scanf("%d", &tmpNode.num);
            rewind(stdin);

            if (c == 'b')
                circle_add(tmpNode);
            else if (c == 'c')
                queue_add(tmpNode);
        }
        else if (c == 'd')
        {
            int index;
            scanf("%d", &index);
            rewind(stdin);
            remove_from_circle(index);
        }
    }
    return 0;
}

