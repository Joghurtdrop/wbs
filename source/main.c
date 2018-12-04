#include <stdio.h>
#include <string.h>
#include "main.h"
#include "astar.h"

void printMatrix();
void initMatrix();
void printUsage();
void addPathToMatrix();
void initWeights();
void initPath();

node* realEnd;

int main(int argc, char const *argv[])
{
    realEnd = malloc(sizeof(node));
    startNode = malloc(sizeof(node));
    endNode  = malloc(sizeof(node));

    startNode->x=0;
    startNode->y=0;
    endNode->x=14;
    endNode->y=14;
    realEnd->x=14;
    realEnd->y=14;

    initPath();
    initMatrix();
    initWeights();
    findPath();
    addPathToMatrix();
    printMatrix();

    return 0;
}

int getIntegerInput()
{
    char *p, s[100];
    int n;

    while(fgets(s, sizeof(s), stdin))
    {
        n = strtol(s, &p, 10);
        if (p == s || *p != '\n')
        {
            printf("Bitte Natürlichezahl eingeben: ");
        } else break;
    }
    printf("\n");
    
    if (n < 0 || n > 14)
    {
        exit(1);
    }

    return n;
}

void initPath()
{
    printf("X-Wert Startpunkt: ");
    startNode->x = getIntegerInput();

    printf("Y-Wert Startpunkt: ");
    startNode->y = getIntegerInput();

    printf("X-Wert Zielpunkt: ");
    endNode->x = getIntegerInput();
    realEnd->x = endNode->x;
    
    printf("Y-Wert Zielpuntk: ");
    endNode->y = getIntegerInput();
    realEnd->y = endNode->y;
   
}

void printUsage()
{
    printf("Usage: a.exe\n");
}

void initWeights()
{
    weight[0] = 4;
    weight[1] = 7;
    weight[2] = 3;
    weight[3] = 6;
    weight[4] = 3;
    weight[5] = 12;
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
    printf("Länge der Strecke: %d", endNode->realDist);
    
}

void addPathToMatrix(){
    while (endNode->pathParent != NULL)
    {
        matrix[endNode->x][endNode->y] = 9;
        endNode = endNode->pathParent;
    }
    matrix[endNode->x][endNode->y] = 9;
}