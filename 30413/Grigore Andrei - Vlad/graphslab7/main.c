#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define UNVISITED 0
#define VISITED 1
#define MAX 50
#define INT_MAX 100
int **adjMat;
int nrOfVert;
int nrOfEdges;
typedef struct node
{
    int data;
    struct node*next;
} NodeT;
typedef struct edge
{
    int weight;
    int source;
    int dest;
}EdgeT;


NodeT *stack;

NodeT *createNode(int data)
{
    NodeT *newNode=(NodeT*)malloc(sizeof(NodeT));
    newNode->data=data;
    newNode->next=NULL;
    return newNode;
}


void push(int data)
{
    NodeT * newH = createNode(data);
    newH->next = stack;
    stack = newH;
}

void pop()
{
    if(stack!=NULL)
    {
        stack=stack->next;
    }
}

NodeT * peekStack()
{
    return stack;
}

int isEmptyStack()
{
    return stack == NULL;
}

void readAdjMatrix(FILE *f)
{
    int n;
    fscanf(f,"%d",&n);
    nrOfVert=n;
    int i,j;
    adjMat=(int**)malloc(sizeof(int*));
    for(i=0; i<n; i++)
    {
        *(adjMat+i)=(int*)malloc(n*sizeof(int));
    }
    EdgeT*edge=(EdgeT*)malloc(MAX*sizeof(EdgeT));
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            fscanf(f,"%d",&adjMat[i][j]);
            edge[i].weight=adjMat[i][j];
        }
        if(edge[i].weight!=0)
        {
            nrOfEdges++;
        }
    }
    fclose(f);
}
void printAdjMatrix()
{
    printf("    ");
    int i,j;
    for(int i=0; i<nrOfVert; i++)
    {
        printf("%c   ",'A'+i);
    }
    printf("\n");
    for(i=0; i<nrOfVert; i++)
    {
        printf("%c ",65+i);
        for(j=0; j<nrOfVert; j++)
        {
            printf("%3d ",adjMat[i][j]);
        }
        printf("\n");
    }
    printf("\n");

}

int getNrOfNeigh(int v)
{
    if(v<nrOfVert)
    {
        int nrOfNeigh=0;
        int i;
        for(i=0; i<nrOfVert; i++)
        {
            if(adjMat[v][i]>0 && i!=v)
            {
                nrOfNeigh++;
            }
        }
        return nrOfNeigh;
    }
    else
    {
        return 0;
    }
}

int *NeighOfVert(int v)
{
    if(v<nrOfVert)
    {
        int nrOfNeigh=getNrOfNeigh(v);
        int *neighbors=(int*)malloc(sizeof(int)*nrOfNeigh);
        int i,j=0;
        for(i=0; i<nrOfVert; i++)
        {
            if(adjMat[v][i]>0 && i!=v)
            {
                neighbors[j]=i;
                j++;
            }
        }
        return neighbors;

    }
    else
    {
        return NULL;
    }
}

void dfs(int startNode)
{
    int *visited=(int*)malloc(nrOfVert*sizeof(int));
    int i,v;
    for(i=0; i<nrOfVert; i++)
    {
        visited[i]=UNVISITED;
    }
    push(startNode);
    while(!isEmptyStack())
    {
        v=peekStack()->data;
        pop();
        if(visited[v]==UNVISITED)
        {
            visited[v]=VISITED;
            int nrOfNeighbors=getNrOfNeigh(v);
            int *neighbors=NeighOfVert(v);
            for(i=nrOfNeighbors-1; i>=0; i--)
            {
                int w=neighbors[i];
                if(visited[w]==UNVISITED)
                {
                    push(w);
                }

            }
            printf("%c ",v+'A');

        }
    }
    printf("\nDFS ENDED\n");

}
void swap(EdgeT*a,EdgeT*b)
{
    EdgeT aux=*a;
    *a=*b;
    *b=aux;
}

void sort(EdgeT *e,int n)
{
    int ok=1;
    while(ok!=0)
    {
        ok=0;
        for(int i=0;i<n;i++)
        {
            if(e[i].weight>e[i+1].weight)
            {
                swap(&e[i],&e[i+1]);
                ok=1;
            }
        }
    }
}

void BellmanFord(EdgeT *e,int startNode)
{
    int *dist=(int*)malloc(MAX*sizeof(int));
    for(int i=0;i<nrOfVert;i++)
    {
        dist[i]=INT_MAX;
    }
    dist[startNode]=0;
    for(int i=0;i<nrOfVert-1;i++)
    {
        for(int j=0;j<nrOfEdges;j++)
        {
            int u=e[j].source;
            int v=e[j].dest;
            int weight=e[j].weight;
            if(dist[u]!=INT_MAX && dist[u]+weight<dist[v])
            {
                dist[v]=dist[u]+weight;
            }
        }
    }
    for(int i=0;i<nrOfEdges;i++)
    {
        int u=e[i].source;
        int v=e[i].dest;
        int weight=e[i].weight;
        if(dist[u]!=INT_MAX && dist[u]+weight<dist[v])
        {
            printf("Graph contains negative weight cycle");
            return;
        }
    }
    for(int i=0;i<nrOfVert;i++)
    {
        printf("%d ",dist[i]);
    }
}
int main()
{
    FILE *f=fopen("input.txt","r");
    EdgeT *e=(EdgeT*)malloc(MAX*sizeof(EdgeT));
    readAdjMatrix(f);
    printAdjMatrix();
    printf("\n%d\n",nrOfEdges);
    BellmanFord(e,0);
    return 0;
}
