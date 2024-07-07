#include<stdio.h>

int CostMatrix[20][20];
struct router
{
    int distance[20];
    int adjnode[20];
} node[20];

void ReadCostMat(int n)
{
    int i, j;
    printf("enter the cost matrix : \n");
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            scanf("%d", &CostMatrix[i][j]);
        }
    }

    // Initialize the distance and adjnode arrays
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            node[i].distance[j] = CostMatrix[i][j];
            node[i].adjnode[j] = j;
        }
        node[i].distance[i] = 0; // Distance to itself is always 0
    }
}

void calRoutTable(int n)
{
    int i, j, k;
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            for(k=0; k<n; k++)
            {
                if(node[i].distance[j] > node[i].distance[k] + node[k].distance[j])
                {
                    node[i].distance[j] = node[i].distance[k] + node[k].distance[j];
                    node[i].adjnode[j] = k;
                }
            }
        }
    }
}

void displayRoutes(int n)
{
    int i, j;
    for(i=0; i<n; i++)
    {
        printf("Router %d :\n", i);
        for(j=0; j<n; j++)
        {
            printf("Node%d via %d : Distance %d\n", j+1, node[i].adjnode[j]+1, node[i].distance[j]);
        }
        printf("\n");
    }
}

int main()
{
    int n;
    printf("enter the number of nodes: ");
    scanf("%d", &n);
    ReadCostMat(n);
    calRoutTable(n);
    displayRoutes(n);
    return 0;
}
