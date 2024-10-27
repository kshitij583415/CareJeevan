#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int match(char str[],char ptr[])
{
    for(int i=0;i<=strlen(str)-strlen(ptr);i++)
    {
        int j;
        for(j=0;j<strlen(ptr);j++)
        {
            if(ptr[j]!=str[i+j])
            break;
        }

        if(j==strlen(ptr))
        return i;
        
    }
    return -1;
}
int main()
{
    printf("Enter the string : ");
    char str[50];
    gets(str);
    printf("Enter the pattern : ");
    char ptr[20];
    gets(ptr);
    printf("after : %d",match(str,ptr));
}