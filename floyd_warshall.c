#include<stdio.h>
#include<stdlib.h>
#define INF 9999
void floyd_warshall(int a[][7],int n)
{
    for(int k=0;k<n;k++)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                int p=a[i][k]+a[k][j];
                if(p<a[i][j])
                a[i][j]=p;
            }
        }
    }
     for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("\nShortest path between %d to %d is %d KM.\n",i,j,a[i][j] );
        }
        printf("\n");
    }
}
int main()
{
     int a[7][7]={{0,0,0,0,0,0,0},
    {0,0,1,1,0,0,0},
    {0,1,0,0,1,0,0},
    {0,1,0,0,1,0,0},
    {0,0,1,1,0,1,1},
    {0,0,0,0,1,0,0},
    {0,0,0,0,1,0,0}};
     for(int i=1;i<7;i++)
     {
        for(int j=1;j<7;j++)
        {
            if(a[i][j]==0)
            a[i][j]=INF;
        }
     }
     floyd_warshall(a,7);
    return 0;
}