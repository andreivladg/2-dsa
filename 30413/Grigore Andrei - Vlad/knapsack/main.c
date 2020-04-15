#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int value;
    int weight;
}Item;

void swap(Item *a,Item *b)
{
    Item *aux=a;
    a=b;
    b=aux;
}

void sort(Item *item,int n)
{
    int ok=1;
    while(ok!=0)
    {
        for(int i=0;i<n;i++)
        {
            if((item[i].value<item[i+1].value)||(item[i].value<item[i+1].value && item[i].weight>item[i+1].weight))
            {
                swap(item+i,item+i+1);
                ok=1;
            }
            else
            {
                ok=0;
            }
        }
    }
}

void greedy(Item*item,int n,int W)
{
    int value=0;
    int weight=0;
    double valueFractional=0.0;
    int weightFractional=0;
    for(int i=0;i<n;i++)
    {
        if(item[i].weight<W)
        {
            value+=item[i].value;
            weight+=item[i].weight;
            valueFractional+=item[i].value;
            weightFractional+=item[i].weight;
            W-=item[i].weight;
        }
        else
        {
            valueFractional+=(double)(W*item[i].value)/item[i].weight;
            weightFractional+=W;
        }
    }
    printf("for 1-0: %d %d\n",weight,value);
    printf("\nFor fractional:%d %lf\n",weightFractional,valueFractional);
}
int main()
{
   FILE *f=fopen("input.txt","r");
   int n,W;
   fscanf(f,"%d %d",&n,&W);
   printf("%d %d",n,W);
   Item*item=(Item*)malloc(n*sizeof(Item));
   for(int i=0;i<n;i++)
   {
       fscanf(f,"%d %d",&item[i].weight,&item[i].value);
       printf("\n%d %d\n",item[i].weight,item[i].value);
   }
   sort(item,n);
   greedy(item,n,W);
    return 0;
}
