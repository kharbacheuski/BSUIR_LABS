#include <stdio.h>
#include <math.h>

double kvadr(double x)
{
    return x*x;
}

int main()
{
    double x,y;
    scanf("%lf", &x);
    scanf("%lf", &y);

    // указатель на используемую функцию
    double (*func) (double);

    int code_func = -1;
    printf("select function (1 - sinh,2 - x^2 ,3 - e^x)\n");
    scanf("%d", &code_func);

    if(code_func == 1)
    {
        func = sinh;
        printf("Function - sh(x)\n");
    }
    else if(code_func == 2)
    {
        func = kvadr;
        printf("Function - x^2\n");
    }
    else if(code_func == 3)
    {
        func = exp;
        printf("Function - exp(x)\n");
    }
    else
    {
        printf("Wrong function number!");
        return 1;
    }

    printf("x*y = %lf\n", x*y);
    if(x*y>0.5 && x*y < 10)
        printf("%lf", exp(func(x)- fabs(y)));
    else if(x*y>0.1 && x*y < 0.5)
        printf("%lf", pow(fabs(func(x)+y), 1.0/3));
    else
        printf("%f", 2*pow(func(x), 2));

    return 0;
}
