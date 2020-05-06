#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int min(int x,int y,int z)
{
    if(x<y && x<z)
    {
        return x;
    }
    if(y<x && y<z)
    {
        return y;
    }
   else
   {
       return z;
   }

}

int editDistDP(char *string1,char *string2,int m,int n)
{
    int L[m+1][n+1];
    for(int i=0;i<=m;i++)
    {
        for(int j=0;j<=n;j++)
        {
            if(i==0)
            {
                L[i][j]=j;
            }
            else if(j==0)
            {
                L[i][j]=i;
            }
            else if(string1[i-1]==string2[j-1])
            {
                L[i][j]=L[i-1][j-1];
            }
            else
            {
                L[i][j]=min(L[i][j-1]+1,L[i-1][j]+1,L[i-1][j-1]+1);
            }
        }
    }
    return L[m][n];
}

int main()
{
    FILE *f=fopen("input.txt","r");
    char*string1,*string2;
    string1=(char*)malloc(sizeof(char)*2000);
    string2=(char*)malloc(sizeof(char)*2000);
    fscanf(f,"%s %s",string1,string2);
    printf("%s %s",string1,string2);
    printf("\n%d",editDistDP(string1,string2,strlen(string1),strlen(string2)));

    return 0;
}
