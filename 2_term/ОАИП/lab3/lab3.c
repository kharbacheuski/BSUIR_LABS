#include <stdio.h>
#include <stdlib.h>

char* make_str_from_char(char c)
{
    char* resp = (char*)malloc(2 * sizeof(char));
    resp[0] = c;
    resp[1] = '\0';
    return resp;
}

char* sign[100];
int i = 0;

void push_sign(char* c)
{
    sign[i++] = c;
}

char* pop_sign()
{
    return (i != 0) ? sign[--i] : NULL;
}

char* var[100];
int j = 0;

void push_var(char* c)
{
    var[j++] = c;
}

char* pop_var()
{
    return (j != 0) ? var[--j] : NULL;
}

int main()
{
    char* str = (char*)malloc(100 * sizeof(char));
    gets(str);

    int k = 0;
    int count = 0;

    char* out;
    while (1)
    {
        char* v = make_str_from_char(str[k]);

        if (str[k] == '+' || str[k] == '-' || str[k] == '*' || str[k] == '/')
        {
            push_sign(v);
            count = 0;
        }
        else
        {
            if (str[k] == '\0')
            {
                while (1)
                {
                    out = pop_var();
                    char* v1 = pop_var();
                    if (v1 == NULL)
                        break;
                    char* sign = pop_sign();
                    strcat(v1, out);
                    strcat(v1, sign);
                    
                    push_var(v1);
                }
                break;
            }
            if (count == 1)
            {
                char* v1 = pop_var();
                char* sign = pop_sign();
                strcat(v1, v);
                strcat(v1, sign);
                char* new_var = v1;
                push_var(new_var);
            }
            else
            {
                push_var(v);
                count++;
            }
        }
        k++;
    }
    printf("%s", out);
}
