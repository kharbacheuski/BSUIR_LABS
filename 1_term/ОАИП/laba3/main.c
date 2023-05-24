#include <stdio.h>
#include <math.h>

double func(double x){
    return (exp(x) - exp(-1*x))/2;
}


double func2(double x, int n)
{
    double s = 0;

    for (int i  = 0; i <= n; i++)
    {
        double fact = 1;
        for(int j = 2*i+1; j > 1; j--)
            fact *= j;

        s += pow(x, 2*i+1)/fact;
    }
    return s;
}

int main() {
    double a,b,n;
    scanf("%lf%lf%lf", &a,&b,&n);

    double x = a;
    while(x>=a && x<=b)
    {
        printf("%5lf\t%15lf\t%15lf\n", x, func(x), func2(x,n));
        x += (b-a)/10.0;
    }

    return 0;
}
