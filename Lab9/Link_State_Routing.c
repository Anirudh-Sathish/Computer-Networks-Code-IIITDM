// @ Author : Anirudh Sathish 
// @ RollNo : CS20B1125 


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define N 20
#define inf 10000



int main()
{
    int routerNumber;
    printf("Enter no of router \n");
    scanf("%d",&routerNumber);
    int adjacencyMatrix[routerNumber][routerNumber];

    int i ,j ;
    printf("Enter the adjacency matrix values \n");
    printf("Enter 10000 to indicate no edge between the matrices\n");
    printf("Take required lengths only below 10000 \n");
    printf("10000 is used to represent infinity \n");
    printf("\n\n Enter adjacency Matrix values \n\n");
    for(i = 0; i < 4 ; i++)
    {
        for(j = 0 ; j < 4; j++)
        {
            scanf("%d",&adjacencyMatrix[i][j]);
        }
    }
    printf("The adjacency Matrix is \n");
    for(i = 0; i < 4 ; i++)
    {
        for(j = 0 ; j < 4; j++)
        {
            printf("%d\t",adjacencyMatrix[i][j]);
        }
        printf("\n");
    }


}