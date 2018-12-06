#include <stdio.h>
#include <string.h>
#include "main.h"
#include "astar.h"

void printMatrix();
void initMatrix();
void printUsage();
void addPathToMatrix();
void initWeights();
void initVerge();

node* realEnd;
FILE *fp;

int main(int argc, char const *argv[])
{
    fp = fopen("S_003_Daten.csv","r");

    realEnd = malloc(sizeof(node));
    startNode = malloc(sizeof(node));
    endNode  = malloc(sizeof(node));

    printf("Im folgenden sind alle Werte 0-Indiziert.\n");

    initVerge();
    initMatrix();
    initWeights();
 
    findPath();
    realEnd = endNode;
    addPathToMatrix();
    printMatrix();

    printf("Press ENTER key to Continue\n");  
    getchar();  
    return 0;
}

int getIntegerInput()
{
    char *isInteger, userInput[100];
    int number;

    while(fgets(userInput, sizeof(userInput), stdin))
    {
        number = strtol(userInput, &isInteger, 10);
        if (isInteger == userInput || *isInteger != '\n')
        {
            printf("Bitte natürliche Zahl eingeben: ");
        } else break;
    }
    
    if (number < 0 || number > 14)
    {
        exit(1);
    }

    return number;
}

void initVerge()
{
    printf("X-Wert Startpunkt: ");
    startNode->x = getIntegerInput();

    printf("Y-Wert Startpunkt: ");
    startNode->y = getIntegerInput();

    printf("X-Wert Zielpunkt: ");
    endNode->x = getIntegerInput();
    
    printf("Y-Wert Zielpuntk: ");
    endNode->y = getIntegerInput();   
}

void printUsage()
{
    printf("Usage: a.exe\n");
}

void initWeights()
{   
    int i=0, j=0;
    char myString [100];

    fscanf(fp,"%s", myString);
    fscanf(fp,"%s", myString);

    while (fscanf(fp,"%d;%*[^;];%d;%*[^\n]", &i, &j) == 2)
    {
        weight[i] = j;
    }
}

void initMatrix()
{
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
    printf("\n");
    for(size_t i = 0; i < 15; i++)
    {
        for(size_t j = 0; j < 15; j++)
        {
            printf("|%d", matrix[j][i]);
        }
        printf("|\n");
    }
    printf("\n");
    printf("StartPunkt: %d, %d\n", startNode->x, startNode->y);
    printf("ZielPunkt: %d, %d\n", realEnd->x, realEnd->y);
    printf("Kosten der Strecke: %d\n", realEnd->realDist);
}

void addPathToMatrix(){
    while (endNode->pathParent != NULL)
    {
        matrix[endNode->x][endNode->y] = 9;
        endNode = endNode->pathParent;
    }
    matrix[endNode->x][endNode->y] = 9;
}