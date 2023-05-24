#include <stdio.h>
#define MAXLEN 1000

int getline(char *str)
{
    int len = 0;
    char c;
    while ( (c = getchar()) != EOF && len < MAXLEN)
    {
        if(c == '\n')
            break;
        *str++ = c;
        len++;
    }
    *str = '\0';
    return len;
}

int main() {

    char str[MAXLEN];
    int len = getline(str);

    char podstr[MAXLEN];
    int ind = 0;

    for (int i = 0; i < len; ++i) {
        if(str[i]>= '0' && str[i] <= '9')
        {
            podstr[ind] = str[i];
            ind++;
        }
    }
    podstr[ind] = '\0';
    printf("%s", podstr);

    return 0;
}
