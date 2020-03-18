#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct node_type
{
    int id;

    struct node_type*left,*right;
} NodeT;
typedef struct node_type2
{
    int data;
    struct node_type2 *next,*prev;
} NodeL;
NodeL *first, *last, *current;

void initializeDll()
{
    first=NULL;
    last=NULL;
}

void addEl(int data)
{
    if(last ==NULL)
    {
        first=(NodeL*)malloc(sizeof(NodeL));
        first->data=data;
        first->next=NULL;
        first->prev=NULL;
        last=first;
    }
    else
    {
        NodeL *newNode=(NodeL*)malloc(sizeof(NodeL));
        last->next=newNode;
        newNode->data=data;
        newNode->prev=last;
        newNode->next=NULL;
        last=newNode;
    }
}
void createList(NodeT*currentNode)
{
    if(currentNode!=NULL)
    {
        addEl(currentNode->id);
        createList(currentNode->left);
        createList(currentNode->right);
    }
    else
    {
       addEl('*');
    }
}
NodeL *getListFromTree(NodeT *root)
{
    initializeDll();
    createList(root);

    return first;

}
void traverseList(NodeL *first)
{
    NodeL *newNode=first;
    while(newNode!=NULL)
    {
        printf("%d",newNode->data);
        newNode=newNode->next;
    }
    printf("\n");
    current=first;
}
NodeT * getTreeFromList()
{
    if(current->data=='*' || current->data==NULL)
    {
        current=current->next;
        return NULL;
    }
    else
    {
         NodeT *newNode = (NodeT*)malloc(sizeof(NodeT));
        newNode->id = current->data;
        current = current->next;
        newNode->left = getTreeFromList();
        newNode->right = getTreeFromList();
        return newNode;
    }

}
void prettyPrint( NodeT *p, int level )
{
    int i;
    if ( p != NULL )
    {
        prettyPrint( p->left, level + 1 );
        for (i = 0; i <= level; i++ )
        {
            printf( "   " );
        }
        printf( "%d\n", p->id );
        prettyPrint( p->right, level + 1 );
    }
}



NodeT *createBinTree(int branch,NodeT *parent)
{
    NodeT *p;
    int id;
    if(branch==0)
        printf("Root identifier[0 to end]=");
    else if(branch==1)
        printf("Left child of %d [0 to end]=",parent->id);
    else
        printf("Right child of %d [0 to end]=",parent->id);
    scanf("%d",&id);
    if(id == 0)
    {
        return NULL;
    }
    else
    {
        p=(NodeT*)malloc(sizeof(NodeT));
        if(p==NULL)
        {
            printf("out of space in createBinTree()");
        }
        p->id=id;
        p->left=createBinTree(1,p);
        p->right=createBinTree(2,p);
    }
    return p;
}

int main()
{
  NodeT *root=createBinTree(0,NULL);
  NodeL *firstFromList=getListFromTree(root);
  traverseList(firstFromList);
  root=getTreeFromList(firstFromList);
  prettyPrint(root,0);


    return 0;
}
