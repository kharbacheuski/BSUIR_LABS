#include <stdio.h>
#include <math.h>

int main()
{
    double x,y,z;
    scanf("%lf", &x);
    scanf("%lf", &y);
    scanf("%lf", &z);
    double s =
            sqrt(10*(pow(x, 1.0/3) + pow(x, y + 2)))*
            ( pow(asin(z), 2) - fabs(x - y) );
    printf("%lf", s);

    return 0;
}
