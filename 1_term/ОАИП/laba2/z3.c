#include <stdio.h>
#include <math.h>


int main()
{
    double x, y, z, a, b, c, rez;
    x = -15.246;
    y = 4.642e-2;
    z = 21;
    a = log(pow(y, -1*sqrt(fabs(x))));
    b = x - 0.5*y;
    c = pow(sin(atan(z)), 2);
    rez = a*b +c;
    printf("%f", rez);
    return 0;
}