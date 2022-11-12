// Anirudh Sathish 
// CS20B1125

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define inf 10000
#define V 4

void FindShortestDistance(int weightMatrix[V][V],int n,int source);

int main()
{
    int weightMatrix[V][V],i,j;

    int graph[V][V] = { { 0,2,0,1},
                        { 2,0,3,7},
                        { 0,3,0,1 },
                        { 1,7,11,0 }};

    printf("\n Routing Table \n");
    for(i = 0 ; i < V ; i++)
    {
        printf("\nRouting Table %d \n ",i);
        FindShortestDistance(graph,V,i);
        printf("\n");
    }

    
    return 0;
}

void FindShortestDistance(int weightMatrix[V][V],int n,int source)
{

    int weight[V][V];
    int distance[V];
    int pred[V];
    bool visited[V];
    int count;
    int minimumDistance ;
    int nextRouter;
    int i,j;

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(weightMatrix[i][j]==0)
                weight[i][j] = inf;
            else
                weight[i][j]=weightMatrix[i][j];
        }
            
    }
        

    for(i=0;i<n;i++)
    {
        distance[i]=weight[source][i];
        pred[i]=source;
        visited[i]=false;
    }
    distance[source]=0;
    visited[source]=true;
    count=1;

    while(count<n-1)
    {
        minimumDistance =inf;
        for(i=0;i<n;i++)
        if(distance[i]<minimumDistance &&!visited[i])
        {
            minimumDistance =distance[i];
            nextRouter=i;
        }
        visited[nextRouter]=true;
        for(i=0;i<n;i++)
            if(!visited[i])
                if(minimumDistance + weight[nextRouter][i]<distance[i])
                {
                    distance[i]=minimumDistance +weight[nextRouter][i];
                    pred[i]=nextRouter;
                }
                count++;
    }
    
    //print the path and distance of each node
    printf("Destination\tDistance\t Path");
    for(i=0;i<n;i++)
    {
        if(i!=source)
        {
            printf("\nRouter %d \t",i);
            printf("%d",i,distance[i]);
            printf("\t\t=> Router %d",i);
            j=i;
            do
            {
                j=pred[j];
                count++;
                printf("<-%d",j);
            }while(j!=source);
        }
    }
}