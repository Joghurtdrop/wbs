#include <stdio.h>
#include <string.h>
#include "main.h"
#include "astar.h"

void printMatrix();
void initMatrix();
void printUsage();

int main(int argc, char const *argv[])
{


    if (!(argc==5)) 
    {
        printUsage();
        return 1;
    }
    else
    {
        startNode = (node*) malloc(sizeof(node));
        endNode  = (node*) malloc(sizeof(node));
        startNode->x = *argv[1]-'0';
        startNode->y = *argv[2]-'0';
        endNode->x = *argv[3]-'0';
        endNode->y = *argv[4]-'0';
    }

    
    

    initMatrix();
    calculate();
    printMatrix();

    return 0;
}

void printUsage()
{
    printf("Usage: a.exe <startx> <starty> <goalx> <goaly>\n");
}

void initMatrix()
{
    FILE *fp;
    fp = fopen("..\\S003\\S_003_Daten.csv","r");    


    for(size_t i = 0; i < 15; i++)
    {
        for(size_t j = 0; j < 15; j++)
        {
            fscanf(fp,"%d;[\n]*", &matrix[i][j]);
        }
    }
}

void printMatrix()
{
    
    for(size_t i = 0; i < 15; i++)
    {
        printf("-------------------------------\n");
        for(size_t j = 0; j < 15; j++)
        {
            printf("|%d", matrix[i][j]);
        }
        printf("|\n");
    }

    printf("StartPunkt: %d, %d\n", startNode->x, startNode->y);
    printf("ZielPunkt: %d, %d\n", endNode->x, endNode->y);
    
}