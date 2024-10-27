#include<stdio.h>
int string_to_num(char str[])
{
    //this function converts a string to its equivalent integer value
    int num=0;
    for(int i=0;str[i]!='\0';i++)
    {
        num=(num*10)+(str[i]-48);
    }
    return num;
}
int main()
{
    char ch[10];
    scanf("%s",ch);
    printf("%d",string_to_num(ch));
    return 0;
}