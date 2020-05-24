#include <stdio.h>
#include <stdlib.h>
#define MAX 50
int arr[MAX];
void printArray(int n)
{

    for(int i=0;i<n;i++)
    {
        printf("%d ",arr[i]);

    }
}

void merge(int top,int mid,int bot)
{
    int index1,index2,index3,l;
    int temp[MAX];
    index1=top;
    index2=mid+1;
    index3=top;
    while(index1<=mid && index2<=bot)
    {
        if(arr[index1]<=arr[index2])
        {
            temp[index3]=arr[index1];
            index1++;
        }
        else
        {
            temp[index3]=arr[index2];
            index2++;
        }
        index3++;
    }
    for(l=index1;l<=mid;l++)
    {
        temp[index3]=arr[l];
        index3++;
    }
    for(l=index2;l<=bot;l++)
    {
        temp[index3]=arr[l];
        index3++;
    }
    for(l=top;l<=bot;l++)
    {
        arr[l]=temp[l];
    }
}

void mergeSort(int top,int bot)
{
    int mid;
    if(top<bot)
    {
        mid=(top+bot)/2;
        mergeSort(top,mid);
        mergeSort(mid+1,bot);
        merge(top,mid,bot);
    }
}

int main()
{
   int i,n;
   printf("Enter nr of elements:");
   scanf("%d\n",&n);
   for(i=0;i<n;i++)
   {
       scanf("%d\n",&arr[i]);
   }
   printArray(n);
   mergeSort(0,n-1);
   printf("\nSorted array:\n");
   printArray(n);
    return 0;
}
