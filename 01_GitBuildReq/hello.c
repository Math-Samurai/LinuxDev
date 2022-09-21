#include<stdio.h>
#include<stdlib.h>

char* readString()
{
    int length = 100;
    char *str = malloc(length);
    if (!str)
    {
        return NULL;
    }

    int iterator = 0;
    char c;
    while ((c = getchar()) != EOF && c != '\n')
    {
        if (iterator == length)
        {
            str = realloc(str, length * 2);
            if (!str)
            {
                return NULL;
            }
        }

        str[iterator] = c;
        ++iterator;
    }

    if (iterator == length)
    {
        str = realloc(str, length + 1);
        if (!str)
        {
            return NULL;
        }
    }

    str[iterator] = 0;
    return str;
}

int main()
{
    char* str = readString();
    if (!str)
    {
        return -1;
    }

    printf("Hello, %s!\n", str);
    free(str);
    return 0;
}
