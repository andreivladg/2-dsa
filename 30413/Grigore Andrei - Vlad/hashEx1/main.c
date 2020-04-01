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


int hash(char *key)
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
    int h=hash(key);
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

void deleteNode(char *key)
{NodeT *p=(NodeT*)malloc(sizeof(NodeT));
    int h=hash(key);
    p=BucketTable[h];
    while(p!=NULL)
    {
        if(strcmp(p->key,key)==0)
        {
            NodeT *aux=p;
            p=p->next;
            free(p);
            BucketTable[h]=NULL;
        }
    }

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
        if(c=='d')
        {
            deleteNode(name);
        }


    }


    return 0;
}
