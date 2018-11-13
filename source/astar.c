#include <stdio.h>
#include <stdlib.h>
#include "astar.h"
#include "main.h"

node *openList = NULL;
node *closedList = NULL;
node *pathList = NULL;


int heuristic(node *position, node *destination)
{
    int x = abs(position->x - destination->x);
    int y = abs(position->y - destination->x);

    return x + y;
}

void calculate()
{
    //node *element = (node*) malloc(sizeof(node));
    startNode->aproxDist = 0 + heuristic(startNode, endNode);
    LL_APPEND(openList, startNode);
    LL_APPEND(pathList, startNode);

}

int isOpenListEmpty()
{
    node *elt = NULL;
    int count = 0;
    LL_COUNT(openList,elt,count);

    return (count = 0);
}


void recursion()
{
    if (isOpenListEmpty())
    {
        exit;
    }

    node *bestGuess = openList;

    node *elt = NULL;
    LL_FOREACH(openList, elt)
    {
        if (bestGuess->aproxDist > elt->aproxDist)
        {
            bestGuess = elt;
        }
    }

    LL_DELETE(openList, bestGuess);
    LL_APPEND(closedList, bestGuess);

    if ((bestGuess->x == endNode->x) && (bestGuess->y == endNode->y))
    {

    }
    
}