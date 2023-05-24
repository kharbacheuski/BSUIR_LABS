#include <stdio.h>
#include <math.h>


double y(double x)
{
    return sqrt(1+x) - 1 - x/2;
}


double s(double x, int e, int *km)
{
    int k = 2;
    double n = trunc(y(x)*pow(10, e)) / pow(10, e);

    double s = 0;
    do {
        double p = pow(-1, k-1) * pow(x, k);
        for(int i = ((2*k-3) % 2)+2; i <= (2*k-3); i += 2)
            p *= i;
        for(int i = ((2*k) % 2)+2; i <= (2*k); i += 2)
            p /= i;

        s+=p;
        k++;
    }
    while( trunc(s * pow(10, e)) / pow(10, e) != n);


    *km = k-2;

    return s;
}


int main()
{
    double a,b;
    int e;
    scanf("%lf%lf%d", &a, &b, &e);
    getchar();

    for(double i = a; i <= b; i += 0.1)
    {
        int k;
        double s_v = s(i, e, &k);
        printf("%lf\t%lf\t%lf\t%d\n", i, y(i), s_v, k);
    }

    return 0;
}
