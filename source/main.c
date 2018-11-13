#include <stdio.h>
#include <string.h>
#include "main.h"

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
        startPunkt[0][0] = *argv[1]-'0';
        startPunkt[0][1] = *argv[2]-'0';
        zielPunkt[0][0] = *argv[3]-'0';
        zielPunkt[0][1] = *argv[4]-'0';

        printf("StartX: %d\n", startPunkt[0][0]);
        printf("StartY: %d\n", startPunkt[0][1]);
        printf("ZielX: %d\n", zielPunkt[0][0]);
        printf("ZielY: %d\n", zielPunkt[0][1]);
    }

    
    

    initMatrix();
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
    
}