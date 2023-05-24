#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,m;
    scanf("%d%d", &n,&m);
    getchar();

    char **matrix;
    matrix = (char **) malloc(sizeof(char) * n);
    for (int i = 0; i < n; ++i)
        matrix[i] = (char *) malloc(sizeof(char) * m);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
        {
            scanf("%c", &matrix[i][j]);
            getchar();
        }

    int k = 0;
    int mask[256] = {0};

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if(mask[(int)matrix[i][j]] == 0)
            {
                mask[(int)matrix[i][j]] = 1;
                k++;
            }
    printf("%d", k);
    return 0;
}
