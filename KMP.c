#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* SetTable(char* pattern)
{
    int len = strlen(pattern);
    int* skip;
    skip = (int*)calloc(sizeof(int), len);

    int pidx = 0;
    for(int i = 1; i < len; i++)
    {
        while (pidx > 0 && pattern[pidx] != pattern[i])
        {
            pidx = skip[pidx-1];
        }
        
        if(pattern[i] == pattern[pidx])
        {
            pidx++;
            skip[i] = pidx;
        }
    }

    return skip;
}
int* KMP(char* text, char* pattern)
{
    int* result = (int*)calloc(sizeof(int), 1000000);
    int pidx = 0;
    int* skip = SetTable(pattern);


    int ridx = 0;
    int len = strlen(text);
    int plen = strlen(pattern);

    for(int i = 0; i < len; i++)
    {
        while (pidx > 0 && text[i] != pattern[pidx])
        {
            pidx = skip[pidx-1];
        }
        if(text[i] == pattern[pidx])
        {
            if(pidx == plen-1)
            {
                ridx++;
                result[ridx] = i-plen+1;
                pidx = skip[pidx];
            }
            else
                pidx++;
        }
    }

    result[0] = ridx;
    return result;
}

int main()
{
    char text[1000000];
    char pattern[1000000];
    
    gets(text);
    gets(pattern);

    int *result = KMP(text, pattern);

    int count = result[0];
    printf("%d\n", count);

    for (int i =0; i < count; i++)
    {
        printf("%d\n", result[i+1]+1);
    }
    return 0;
}