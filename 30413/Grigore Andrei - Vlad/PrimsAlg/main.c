#include <stdio.h>
#include <stdlib.h>
#define UNVISITED 0
#define VISITED 1
#define MAX 100
int nrOfVerts;
int **adjMat;
typedef struct node
{
    int data;
    struct node *next;
}NodeT;
NodeT*queue,*stack;
NodeT *createNode(int data)
{
    NodeT *newN=(NodeT*)malloc(sizeof(NodeT));
    newN->data=data;
    newN->next=NULL;
    return newN;
}
typedef struct edge
{
    int weight;
    int source;
    int dest;
}EdgeT;

void readAdjMatrix(FILE *f)
{
    int n;
    fscanf(f,"%d",&n);
    nrOfVerts=n;
    int i,j;
    adjMat=(int**)malloc(sizeof(int*));
    for(i=0; i<n; i++)
    {
        *(adjMat+i)=(int*)malloc(n*sizeof(int));
    }
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            fscanf(f,"%d",&adjMat[i][j]);
        }
    }
    fclose(f);
}

void printAdjMatrix()
{
    printf("    ");
    int i,j;
    for(int i=0; i<nrOfVerts; i++)
    {
        printf("%c   ",'A'+i);
    }
    printf("\n");
    for(i=0; i<nrOfVerts; i++)
    {
        printf("%c ",65+i);
        for(j=0; j<nrOfVerts; j++)
        {
            printf("%3d ",adjMat[i][j]);
        }
        printf("\n");
    }
    printf("\n");

}
EdgeT getMinEdgeForVisitedNodes(int *visited)
{
    EdgeT minimumEdge;
    minimumEdge.weight=MAX;
    for(int i=0;i<nrOfVerts;i++)
    {
        for(int j=0;j<nrOfVerts;j++)
        {
            if(visited[i]==VISITED && visited[j]==UNVISITED && adjMat[i][j]>0)
            {
                if(adjMat[i][j]<minimumEdge.weight)
                {
                    minimumEdge.source=i;
                    minimumEdge.dest=j;
                    minimumEdge.weight=adjMat[i][j];
                }
            }
        }
    }
    return minimumEdge;
}

void printEdges(EdgeT *edges,int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        printf("%c -> %c\t",edges[i].source+'A',edges[i].dest+'A');
    }
    printf("\n");
}

void Prim(int startNode)
{
    printf("\nPrim STARTED\n");
    int nrOfVertsVisited=0,i,minCost=0;
    int *visited=(int*)malloc(sizeof(int)*nrOfVerts);
    for(i=0;i<nrOfVerts;i++)
    {
        visited[i]=UNVISITED;
    }

    EdgeT *edges=(EdgeT*)malloc(sizeof(EdgeT)*(nrOfVerts-1));
    visited[startNode]=VISITED;
    nrOfVertsVisited++;
    while(nrOfVertsVisited<nrOfVerts-1)
    {
        EdgeT minEdge=getMinEdgeForVisitedNodes(visited);
        visited[minEdge.dest]=VISITED;
        edges[nrOfVertsVisited++]=minEdge;
        minCost+=minEdge.weight;
    }
    printEdges(edges,nrOfVertsVisited);
    printf("\nCost of MST:%d\n",minCost);
    printf("\nPrim Ended\n");
}



int main()
{
    FILE *f=fopen("matrix.txt","r");
    readAdjMatrix(f);
    printAdjMatrix();
    Prim(0);
    return 0;
}
