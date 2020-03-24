#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int key;
    struct node *left, *right;
    int height;
} NodeT;

NodeT *createNode(int key)
{
    NodeT *p=(NodeT*)malloc(sizeof(NodeT));
    if(p)
    {
        p->key=key;
        p->left=p->right=NULL;
        p->height=1;
    }
    return p;
}

int height(NodeT *p)
{
    if(p==NULL)
    {
        return 0;
    }
    return p->height;
}

int max(int a,int b)
{
    if(a>b)
        return a;
    else
        return b;
}

int getBalance(NodeT *p)
{
    if(p==NULL)
    {
        return 0;
    }
    return height(p->left)-height(p->right);
}

NodeT *rotateRight(NodeT *p)
{
    NodeT *aux=p->left;
    NodeT *temp=aux->right;

    aux->right=p;
    p->left=temp;

    p->height=max(height(p->left),height(p->right)+1);
    aux->height=max(height(aux->left),height(aux->right+1));

    return aux;
}

NodeT *rotateLeft(NodeT *p)
{
    NodeT *aux=p->right;
    NodeT *temp=aux->left;

    aux->left=p;
    p->right=temp;

    p->height=max(height(p->left),height(p->right)+1);
    aux->height=max(height(aux->left),height(aux->right)+1);

    return aux;
}

NodeT *insertNode(NodeT *p,int key)
{
    if(p==NULL)
    {
        return createNode(key);
    }
    if(key<p->key)
    {
        p->left=insertNode(p->left,key);
    }
    else if(key>p->key)
    {
        p->right=insertNode(p->right,key);
    }
    else
        return p;

    p->height=1+max(height(p->left),height(p->right));

    int balance=getBalance(p);


    if(balance>1 && key<p->left->key)
    {
        return rotateRight(p);
    }

    if(balance<-1 && key>p->right->key)
    {
        return rotateLeft(p);
    }

    if(balance>1 && key>p->left->key)
    {
        p->left=rotateLeft(p->left);
        return rotateRight(p);
    }

    if(balance<-1 && key<p->right->key)
    {
        p->right=rotateRight(p->right);
        return rotateLeft(p);
    }

    return p;
}

void preorder(NodeT *p)
{
    if(p!=NULL)
    {
        printf("%d ",p->key);
        preorder(p->left);
        preorder(p->right);
    }
}

void prettyPrint(NodeT *p,int level)
{
    if(p==NULL)
    {
        return;
    }
    prettyPrint(p->right,level+1);
    for(int i=0; i<=level; i++)
    {
        printf("  ");
    }
    printf("%d\n",p->key);
    prettyPrint(p->left,level+1);
}

int main()
{
    NodeT *root=NULL;
    int n;
    printf("enter nr of nodes: ");
    scanf("%d",&n);
    for(int i=0; i<n; i++)
    {
        int key;
        scanf("%d",&key);
        root=insertNode(root,key);
    }
    preorder(root);
    printf("\n");
    insertNode(root,5);
    insertNode(root,4);
    insertNode(root,7);
    insertNode(root,3);
    prettyPrint(root,0);
    return 0;
}
