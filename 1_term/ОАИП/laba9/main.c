#include <stdio.h>
#include <math.h>

double func(double x, int n)
{
    double a;
    printf("a%d=", n);
    scanf("%lf", &a);

    if(n==0)
        return a;

    return a*pow(x,n) + func(x,n - 1);
}

int main()
{
    int n;
    double x;
    printf("n=");
    scanf("%d", &n);
    printf("x=");
    scanf("%lf", &x);

    double sum = func(x,n);
    printf("\nsum = %lf", sum);
    return 0;
}
