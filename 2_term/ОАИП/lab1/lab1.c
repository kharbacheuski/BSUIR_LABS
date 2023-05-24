#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEFAULT_LENGTH 10

struct Book
{
    char* lastName;
    char* title;
    short year;
};

int alg_one(struct Book lib, char* name, char* title, int year)
{
    
    if (strcmp(lib.lastName, name) == 0 && lib.year >= year)
        return 1;
    return 0;
}

int alg_two(struct Book lib, char* name, char* title, int year)
{
    if (strcmp(lib.title, title) == 0)
        return 1;
    return 0;
}

int getstr(char* str)
{
    int maxLen = DEFAULT_LENGTH;
    int i = 0;
    char c;
    while ((c = getchar()) != '\n')
    {
        if (i >= maxLen)
        {
            realloc(str, i + 5);
            maxLen = i + 5;
        }
        str[i++] = c;
    }

    str[i] = '\0';
    rewind(stdin);
    return i;
}

struct Book* search(struct Book* lib, int count,
    char* name, char* title,
    int year, int (*alg) (struct Book, char*, char*, int),
    int* len)
{
    int resp_count = 0;
    struct Book* resp = (struct Book*)malloc(1 * sizeof(struct Book));

    for (int i = 0; i < count; i++)
    {
        if (alg(lib[i], name, title, year))
        {
            resp = (struct Book*)realloc(resp, sizeof(struct Book)*(resp_count + 1));
            resp[resp_count++] = lib[i];
        }
    }
    *len = resp_count;
    return resp;
}


void out(struct Book b)
{
    printf("----------------------\n");
    printf("%s %s (%d)\n", b.lastName, b.title, b.year);
    printf("----------------------\n");
}

int main()
{
    struct Book* library = (struct Book*)malloc(1 * sizeof(struct Book));
    if (library == NULL)
        return 1;
    int count = 0;

    char code = ' ';
    while (1)
    {
        printf("a - Search author's book after year\n");
        printf("b - Search author's book\n");
        printf("c - Add book\n");

        code = getchar();
        getchar();
        if (code == 'a')
        {
            char* tmp_name = (char*)malloc(DEFAULT_LENGTH * sizeof(char));
            int tmp_year;
            printf("author: ");
            getstr(tmp_name);
            printf("year: ");
            scanf("%d", &tmp_year);
            rewind(stdin);
            // search
            int len = 0;
            struct Book* arr = search(library, count, tmp_name, NULL, tmp_year, alg_one, &len);
            for (int i = 0; i < len; i++)
                out(arr[i]);
            free(tmp_name);
        }
        else if (code == 'b')
        {
            char* tmp_title = (char*)malloc(DEFAULT_LENGTH * sizeof(char));
            printf("title: ");
            getstr(tmp_title);

            // search
            int len = 0;
            struct Book* arr = search(library, count, NULL, tmp_title, -1, alg_two, &len);
            for (int i = 0; i < len; i++)
                out(arr[i]);
            free(tmp_title);
        }
        else if (code == 'c')
        {
            struct Book b;
            b.lastName = (char*)malloc(DEFAULT_LENGTH * sizeof(char));
            b.title = (char*)malloc(DEFAULT_LENGTH * sizeof(char));
            
            printf("author: ");
            int nameLen = getstr(b.lastName);
            printf("title: ");
            int titleLen = getstr(b.title);
            printf("year: ");
            scanf("%d", &b.year);
            rewind(stdin);

            library = (struct Book*) realloc(library, (count + 1)*sizeof(struct Book));
            library[count++] = b;
        }
    }
    free(library);
    return 0;
}


