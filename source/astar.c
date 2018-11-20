#include <stdio.h>
#include <stdlib.h>
#include "astar.h"
#include "main.h"

node *openList = NULL;
node *closedList = NULL;
node *pathList = NULL;

//https://troydhanson.github.io/uthash/

int recursion();

int heuristic(node *position, node *destination)
{
    int x = abs(position->x - destination->x);
    int y = abs(position->y - destination->x);

    return x + y;
}

void calculate()
{
    startNode->realDist = 0;
    startNode->aproxDist = startNode->realDist + heuristic(startNode, endNode);
    startNode->pathParent = NULL;

    LL_APPEND(openList, startNode);
    LL_APPEND(pathList, startNode);

    recursion();
}

int isOpenListEmpty()
{
    node *elt = NULL;
    int count = 0;
    LL_COUNT(openList,elt,count);

    return (count = 0);
}

int areNodesEqual(node *node1, node *node2)
{
    if ((node1->x == node2->x) && (node1->y == node2->y))
    {
        return 0;
    }

    return 1;
}

node* createNeighbourList(node *currentNode)
{
    node *testN = malloc(sizeof(node));   
    testN->x = currentNode->x;
    testN->y = (currentNode->y == 0)?0:(currentNode->y)-1;
    testN->realDist = currentNode->realDist + weight[matrix[testN->x][testN->y]];
    testN->aproxDist = testN->realDist + 1;
    testN->pathParent = currentNode;
    
    node *testS = malloc(sizeof(node));
    testS->x = currentNode->x;
    testS->y = (currentNode->y == 14)?14:(currentNode->y)+1;
    testS->realDist = currentNode->realDist + weight[matrix[testS->x][testS->y]];
    testS->aproxDist = testS->realDist + 1;
    testS->pathParent = currentNode;

    node *testO = malloc(sizeof(node));
    testO->x = currentNode->x;
    testO->x = (currentNode->x == 14)?14:(currentNode->x)+1;
    testO->realDist = currentNode->realDist + weight[matrix[testO->x][testO->y]];
    testO->aproxDist = testO->realDist + 1;
    testO->pathParent = currentNode;

    node *testW = malloc(sizeof(node));
    testW->x = currentNode->x;
    testW->x = (currentNode->x == 0)?0:(currentNode->x)-1;
    testW->realDist = currentNode->realDist + weight[matrix[testW->x][testW->y]];
    testW->aproxDist = testW->realDist + 1;
    testW->pathParent = currentNode;

    node* neighbourList = NULL;

    LL_APPEND(neighbourList, testN);
    LL_APPEND(neighbourList, testS);
    LL_APPEND(neighbourList, testO);
    LL_APPEND(neighbourList, testW);

    return neighbourList;
}


int recursion()
{
    if (isOpenListEmpty())
    {
        return 1;
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

    if (areNodesEqual(bestGuess, endNode))
    {
        return 0;
    }    
    
    node *neighbourList = createNeighbourList(bestGuess);
    node *neighbour;
    node *out = NULL;
    
    LL_FOREACH(neighbourList, neighbour)
    {
        LL_SEARCH(openList, out, neighbour, areNodesEqual);
        if (out == NULL){
            LL_SEARCH(closedList, out, neighbour,areNodesEqual);
        }

        if (out == NULL){
           LL_APPEND(openList, neighbour);
        } else if (neighbour->realDist < out->realDist) {
            LL_DELETE(openList, out);
            LL_DELETE(closedList, out);
            free(out);
            LL_APPEND(openList, neighbour);
        }
    }

    return recursion();
}