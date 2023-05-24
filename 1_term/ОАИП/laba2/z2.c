#include <stdio.h>
#include <math.h>


int main()
{
    double x,y;
    scanf("%lf", &x);
    scanf("%lf", &y);

    if(x*y>0.5 && x*y < 10)
    {
        int code_func = 1;
        printf("set function (1 - sinh,2 - x^2 ,3 - e^x)\n");
        scanf("%d", &code_func);
        if(code_func == 1)
        {
            printf("%lf", exp(sinh(x)- fabs(y)));
        }
        else if(code_func == 2)
            printf("%lf", exp(x*x- fabs(y)));
        else if(code_func == 3)
            printf("%lf", exp(exp(x)- fabs(y)));
        else
        {
            printf("Wrong function number");
            return 1;
        }

    }
    else if(x*y>0.1 && x*y < 0.5)
    {
        int code_func = 1;
        printf("set function (1 - sinh,2 - x^2 ,3 - e^x)\n");
        scanf("%d", &code_func);

        if(code_func == 1)
            printf("%lf", pow(fabs(sinh(x)+y), 1.0/3));
        else if(code_func == 2)
            printf("%lf", pow(fabs(x*x+y), 1.0/3));
        else if(code_func == 3)
            printf("%lf", pow(fabs(exp(x)+y), 1.0/3));
        else
        {
            printf("Wrong function number");
            return 1;
        }
    }
    else
    {
        int code_func = 1;
        printf("set function (1 - sinh,2 - x^2 ,3 - e^x)\n");
        scanf("%d", &code_func);

        if(code_func == 1)
            printf("%f", 2*pow(sinh(x), 2));
        else if(code_func == 2)
            printf("%f", 2*pow(x*x, 2));
        else if(code_func == 3)
            printf("%d", 2*pow(exp(x),2));
        else
        {
            printf("Wrong function number");
            return 1;
        }
    }

    return 0;
}
