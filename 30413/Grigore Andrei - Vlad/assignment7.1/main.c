#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define B 50
typedef struct cell
{
    char key[60];
    struct cell*next;
} NodeT;

typedef struct el
{
    NodeT *first,*last;
} Table;

NodeT *BucketTable[B];

NodeT *initializeHash()
{
    for(int i=0; i<B; i++)
    {
        BucketTable[i]=NULL;
    }
    return BucketTable[B];
}

int hashFunction1(char * key, int i)
{
    int length = strlen(key);
    int k, sum;
    for (sum=0, k=0; k < length; k++)
    {
        sum += key[k];
    }
    return (sum+i) % B;
}

int hashFunction2(char *key)
{
    int sum,len;
    sum=0;
    len=strlen(key);
    for(int i=0; i<len; i++)
    {
        sum+=key[i];
    }
    return (sum%B);

}
int hashFunction3(char *key)
{
    int sum,len;
    sum=0;
    len=strlen(key);
    for(int i=0;i<len;i++)
    {
        sum+=key[i]
    }
    return ((sum*2)%B);
}
NodeT *findNode(char *key)
{
    NodeT *p=(NodeT*)malloc(sizeof(NodeT));
    int h=hash(key);
    p=BucketTable[h];
    while(p!=NULL)
    {
        if(strcmp(key,p->key)==0)
        {
            return p;
        }
        p=p->next;
    }
    return NULL;
}

NodeT *insertNode(char *key)
{
    NodeT *p=(NodeT*)malloc(sizeof(NodeT));
    int h;
    if(p)
    {
        strcpy(p->key,key);
        p->next=NULL;
        h=hash(p->key);
        if(BucketTable[h]==NULL)
        {
            BucketTable[h]=p;
            p->next=NULL;
        }
    }
    else
    {
        NodeT *q=(NodeT*)malloc(sizeof(NodeT));
        q=findNode(p->key);
        if(q==0)
        {
            p->next=BucketTable[h];
            BucketTable[h]=p;
        }
    }
    return p;
}
NodeT *deleteNode(char *key)
{
    NodeT *p=(NodeT*)malloc(sizeof(NodeT));
    int h=hash(key);
    while(BucketTable[h]!=NULL)
    {
        p=BucketTable[h];
        BucketTable[h]=BucketTable[h]->next;
    }
        if(p!=NULL)
        {
            p->next=BucketTable[h]->next;
        }

    free(p);
    return BucketTable[h];
}

void printBucket()
{
    NodeT *p=(NodeT*)malloc(sizeof(NodeT));
    for(int i=0; i<B; i++)
    {
        if(BucketTable[i]!=NULL)
        {
            p=BucketTable[i];
            while(p!=NULL)
            {
                printf("\nBucket for hash value %d\n",i);
                printf("%s\n",p->key);
                p=p->next;
            }
        }
    }
}


int main()
{
    FILE *f=fopen("input.txt","r");
    NodeT *p=NULL;
    char name[60];
    char c;
    for(int i=0; i<B; i++)
    {
        BucketTable[i]=initializeHash();
    }

    while(fscanf(f,"%s",name)!=-1)
    {
        c=*name;
        strcpy(name,name+1);
        if(c=='i')
        {
            p=insertNode(name);
        }
        if(c=='f')
        {
            p=findNode(name);
            if(p!=NULL)
            {
                printf("\nYES\n");
            }
            else
            {
                printf("\nNO\n");
            }
        }
        if(c=='l')
        {
            printBucket();
        }


    }


    return 0;
}
