#include <stdio.h>
#define NAMELEN 100
#define NALOG 0.12


struct employee
{
    char name[NAMELEN];
    int number;
    int hours;
    double tarif;
};


int main()
{
    struct employee empls[10];
    int n;
    printf("Count of employees:");
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; ++i)
    {
        struct employee tmp;
        printf("Name:");
        gets(tmp.name);

        tmp.number = i+1;
        printf("Hours:");
        scanf("%d", &tmp.hours);
        getchar();

        printf("tarif:");
        scanf("%lf", &tmp.tarif);
        getchar();

        empls[i] = tmp;
    }

    for (int i = 0; i < n; ++i)
    {
        double salry;
        if(empls[i].hours > 144)
            salry = empls[i].tarif * 144 + 2*empls[i].tarif * (empls[i].hours - 144);
        else
            salry = empls[i].tarif * (empls[i].hours % 144);
        salry *= 1-NALOG;
        printf("\nsalry of %s = %lf", empls[i].name, salry);
    }
    return 0;
}