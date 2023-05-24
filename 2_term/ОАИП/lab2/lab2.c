#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEFAULT_LENGTH 100

struct Person
{
    char name[DEFAULT_LENGTH];
    
    union currency
    {
        unsigned int wallet[4];
        struct
        {
            unsigned int usd : sizeof(int);
            unsigned int eur : sizeof(int);
            unsigned int byn : sizeof(int);
            unsigned int rub : sizeof(int);
        } currency;
        
    }wallet;
};

unsigned int sum(struct Person p)
{
    return
        p.wallet.currency.usd +
        p.wallet.currency.byn +
        p.wallet.currency.eur +
        p.wallet.currency.rub;
}

void print(struct Person p)
{
    printf("------------\n");
    printf("%s %d\n", p.name, sum(p));
    printf("------------\n");
}

int main()
{
    struct Person* people = (struct Person*)malloc(1 * sizeof(struct Person));
    int count = 0;

    char code = ' ';
    while (1)
    {
        printf("a - More richer than others\n");
        printf("b - Less richer than others\n");
        printf("c - The richest in byn\n");
        printf("d - Add person\n");

        code = getchar();
        getchar();
        if (code == 'a')
        {
            unsigned int max = 0;
            int ind = 0;
            for (int i = 0; i < count; i++)
            {
                unsigned int tmp_sum = sum(people[i]);
                if (tmp_sum > max)
                {
                    max = tmp_sum;
                    ind = i;
                }
            }
            print(people[ind]);
        }
        else if (code == 'b')
        {
            unsigned int min = ~0;
            int ind = 0;
            for (int i = 0; i < count; i++)
            {
                unsigned int tmp_sum = sum(people[i]);
                if (tmp_sum < min)
                {
                    min = tmp_sum;
                    ind = i;
                }
            }
            print(people[ind]);
        }
        else if (code == 'c')
        {
            unsigned int max = 0;
            int ind = 0;
            for (int i = 0; i < count; i++)
            {
                if (people[i].wallet.currency.byn > max)
                {
                    max = people[i].wallet.currency.byn;
                    ind = i;
                }
            }
            print(people[ind]);
        }
        else if (code == 'd')
        {
            struct Person b;
            printf("name: ");
            gets(b.name);
            rewind(stdin);
            printf("usd: ");
            unsigned int usd;
            scanf("%d", &usd);
            b.wallet.currency.usd = usd;

            printf("eur: ");
            unsigned int eur;
            scanf("%d", &eur);
            b.wallet.currency.eur = eur;

            printf("byn: ");
            unsigned int byn;
            scanf("%d", &byn);
            b.wallet.currency.byn = byn;

            printf("rub: ");
            unsigned int rub;
            scanf("%d", &rub);
            b.wallet.currency.rub = rub;

            rewind(stdin);

            people = (struct Person*)realloc(people, sizeof(struct Person)*(count + 1));
            people[count++] = b;
        }
    }
    free(people);
}
