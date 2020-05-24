#include <stdio.h>
#include <stdlib.h>
#define MAX 50
int arr[MAX];
void printArray(int n)
{

    for(int i=0; i<n; i++)
    {
        printf("%d ",arr[i]);

    }
}

void merge(int bot,int mid,int top)
{
    int index1,index2,index3,l;
    int temp[MAX];
    index1=bot;
    index2=mid+1;
    index3=bot;
    while(index1<=mid && index2<=top)
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
    for(l=index1; l<=mid; l++)
    {
        temp[index3]=arr[l];
        index3++;
    }
    for(l=index2; l<=top; l++)
    {
        temp[index3]=arr[l];
        index3++;
    }
    for(l=bot; l<=top; l++)
    {
        arr[l]=temp[l];
    }
}

void mergeSort(int bot,int top)
{
    int mid;
    if(bot<top)
    {
        mid=(top+bot)/2;
        mergeSort(bot,mid);
        mergeSort(mid+1,top);
        merge(bot,mid,top);
    }
}
int interpolationSearch(int arr[],int n,int key)
{
    int low=0;
    int high=n-1;
    int mid;
    while((arr[high]!=arr[low]) && (key>=arr[low]) && (key<=arr[high]))
    {
        mid=low+((key-arr[low])*(high-low)/(arr[high]-arr[low]));

        if(key==arr[mid])
        {
            return mid;
        }
        if(key<arr[mid])
        {
            high=mid-1;
        }
        else
        {
            low=mid+1;
        }
    }

}

int main()
{
    int i,n;
    printf("Enter nr of elements:");
    scanf("%d\n",&n);
    for(i=0; i<n; i++)
    {
        scanf("%d\n",&arr[i]);
    }
    printArray(n);
    mergeSort(0,n-1);
    printf("\nSorted array:\n");
    printArray(n);
    int key;
    scanf("\n%d\n",&key);
    int index=interpolationSearch(arr,n,key);
    printf("Element found at index %d",index);
    return 0;
}
