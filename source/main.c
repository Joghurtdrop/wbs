#include <stdio.h>
#include <string.h>
#include "main.h"
#include "astar.h"

void printMatrix();
void initMatrix();
void printUsage();
void addPathToMatrix();


node* realEnd;

int main(int argc, char const *argv[])
{


    if (!(argc==1)) 
    {
        printUsage();
        return 1;
    }
    else
    {
        realEnd = malloc(sizeof(node));
        startNode = (node*) malloc(sizeof(node));
        endNode  = (node*) malloc(sizeof(node));
        // startNode->x = *argv[1]-'0';
        // startNode->y = *argv[2]-'0';
        // endNode->x = *argv[3]-'0';
        // endNode->y = *argv[4]-'0';
        // realEnd->x = *argv[3]-'0';
        // realEnd->y = *argv[4]-'0';
        startNode->x = 0;
        startNode->y = 0;
        endNode->x = 13;
        endNode->y = 14;
        realEnd->x = endNode->x;
        realEnd->y = endNode->y;
    }

    
    

    initMatrix();
    calculate();
    addPathToMatrix();
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
            fscanf(fp,"%d;[\n]*", &matrix[j][i]);
        }
    }
}

void printMatrix()
{
    
    for(size_t i = 0; i < 15; i++)
    {
        //printf("-------------------------------\n");
        for(size_t j = 0; j < 15; j++)
        {
            printf("|%d", matrix[j][i]);
        }
        printf("|\n");
    }

    printf("StartPunkt: %d, %d\n", startNode->x, startNode->y);
    printf("ZielPunkt: %d, %d\n", realEnd->x, realEnd->y);
    
}

void addPathToMatrix(){
    while (endNode->pathParent != NULL)
    {
        matrix[endNode->x][endNode->y] = 9;
        endNode = endNode->pathParent;
    }
    matrix[endNode->x][endNode->y] = 9;
}