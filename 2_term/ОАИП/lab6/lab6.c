#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* CharToString(char ch)
{
    char* resp = (char*) malloc(2 * sizeof(char));
    resp[0] = ch;
    resp[1] = '\0';
    return resp;
}

char separators[] = {' ', ',', '.', '!', '?',':', ';' };

int IsSeparator(char c)
{
    int status = 0;
    for (int i = 0; i < 7 && status == 0; i++)
        status |= (c == separators[i]) ? 1 : 0;
    return status;
}

char** GetWords(FILE* file, int *n)
{
    int count = 100;
    char** words = (char**)malloc(count * sizeof(char*));
    for (int j = 0; j < count; j++)
    {
        words[j] = (char*)malloc(100 * sizeof(char));
        words[j][0] = '\0';
    }
    int i = 0;
    char c;
    while ((c = fgetc(file)) != EOF)
    {
        if (IsSeparator(c))
            i++;
        else
            strcpy(words[i], strcat(words[i], CharToString(c)));
    }
    *n = i;
    return words;
}

char** GetSeparators(FILE* file)
{
    int count = 100;
    char** separators = (char**)malloc(count * sizeof(char*));
    for (int j = 0; j < count; j++)
    {
        separators[j] = (char*)malloc(100 * sizeof(char));
        separators[j][0] = '\0';
    }
    int i = 0;
    char c;
    while ((c = fgetc(file)) != EOF)
    {
        if (IsSeparator(c))
        {
            strcpy(separators[i], CharToString(c));
            i++;
        }
    }
    return separators;
}

void Replace(char** words, int count, char* target, char* str)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(words[i], target) == 0)
            strcpy(words[i], str);
    }
}

int main()
{
    FILE* f2 = fopen("f2.txt", "r+");
    int n2;
    char** words2 = GetWords(f2, &n2);
    fclose(f2);

    FILE* f1 = fopen("f1.txt", "r+");
    int n1;
    char** words1 = GetWords(f1, &n1);

    fseek(f1,0,0);
    char** seps1 = GetSeparators(f1);
    fclose(f1);

    for (int j = 0; j <= n1; j++)
        printf("%s%s", words1[j], seps1[j]);
    
    // replacing
    for (int i = 0; i < n2; i+=2)
        Replace(words1, n1, words2[i], words2[i + 1]);

    printf("\n");
    for (int j = 0; j <= n1; j++)
        printf("%s%s", words1[j], seps1[j]);

    FILE* g = fopen("g.txt", "w+");
    for (int j = 0; j <= n1; j++)
        fprintf(g, "%s%s", words1[j], seps1[j]);
    fclose(g);
    return 0;
}
